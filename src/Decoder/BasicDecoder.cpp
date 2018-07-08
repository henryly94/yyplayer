#include "BasicDecoder.h"

//include <libavformat/avformat.h>

BasicDecoder::BasicDecoder(){
	imgWidth = 0;
	imgHeight = 0;
	frameBuffer = NULL;
	av_register_all();
}

BasicDecoder::~BasicDecoder(){
	if (frameBuffer != NULL){
		delete frameBuffer;
	}
}

int BasicDecoder::loadVideo(char* filename){
    pFormatCtx = avformat_alloc_context();
	if (avformat_open_input(&pFormatCtx, filename, NULL, NULL)!= 0){
		printf("Failed when trying to open file at: %s\n", filename);
		return -1;
	}

	if(avformat_find_stream_info(pFormatCtx, NULL) < 0){
    	printf("Failed when trying to read stream info!\n");
		return -1;
	}

	av_dump_format(pFormatCtx, -1, filename, 0);
	videoStream = -1;
  	for(int i = 0; i<pFormatCtx->nb_streams; i++) {
    	if( pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			break;
		}
	}

 	if(videoStream == -1) return -1;
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;
 	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	
	if(pCodec == NULL) return -1;
 	if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0)return -1;
	
	pFrame = av_frame_alloc();
  	if(pFrame == NULL) return -1;
 
	pFrameRGB = av_frame_alloc();
 	if(pFrameRGB == NULL) return -1;
	numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);	
	frameBuffer = (char*)av_malloc(numBytes);
 	av_image_fill_arrays(
			pFrameRGB->data,
			pFrameRGB->linesize,
			(uint8_t*)frameBuffer,
			AV_PIX_FMT_RGB24,
			pCodecCtx->width,
			pCodecCtx->height,
			1);
	imgWidth = pCodecCtx->width;
	imgHeight = pCodecCtx->height;	
}

char* BasicDecoder::getNextFrame(){
	while(av_read_frame(pFormatCtx, &packet) >= 0 ) {
    	if(packet.stream_index == videoStream) {
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
 			if(frameFinished) {
				struct SwsContext *img_convert_ctx = NULL;
				img_convert_ctx = 
					sws_getCachedContext(img_convert_ctx, pCodecCtx->width,
							pCodecCtx->height, pCodecCtx->pix_fmt,
							pCodecCtx->width, pCodecCtx->height,
							AV_PIX_FMT_RGB24, SWS_BICUBIC,
							NULL, NULL, NULL);
				if(!img_convert_ctx) {
					fprintf(stderr, "Cannot initialize sws conversion context\n");
					exit(1);
				}
				sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data,
						pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
						pFrameRGB->linesize);
				return frameBuffer;			
			}
			av_free_packet(&packet);
		}
	}
	return NULL;
}

int BasicDecoder::getImgWidth(){
	return imgWidth;
}

int BasicDecoder::getImgHeight(){
	return imgHeight;
}

/*
int main(){
	BasicDecoder decoder;

	return 0;
}
*/
