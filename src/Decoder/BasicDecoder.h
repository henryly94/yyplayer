#pragma once

extern "C"{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/frame.h>
}
#include <stdio.h>
#include <stdlib.h>

class BasicDecoder{
	public:
		BasicDecoder();
		~BasicDecoder();
	
		int getImgWidth();
		int getImgHeight();

		char* getNextFrame();
			
		int loadVideo(char* filename);

	private:
		int imgWidth;
		int imgHeight;
		
		char* frameBuffer;
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

