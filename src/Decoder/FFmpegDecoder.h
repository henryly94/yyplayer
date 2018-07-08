#pragma once

#include "BasicDecoder.h"

extern "C"{
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/imgutils.h>
	#include <libavutil/frame.h>
}


class FFmpegDecoder : public BasicDecoder{
	
	public:
		FFmpegDecoder();
		~FFmpegDecoder();
		
		uint8_t* getNextFrame();

		int loadVideo(char* filename);
		

	private:
		uint8_t* frameBuffer;
		AVFormatContext *pFormatCtx = NULL;
		int videoStream;
		AVCodecContext *pCodecCtx;
		AVCodec *pCodec;
		AVFrame *pFrame;
		AVFrame *pFrameRGB;
		AVPacket packet;
		int frameFinished;
		int numBytes;

};
