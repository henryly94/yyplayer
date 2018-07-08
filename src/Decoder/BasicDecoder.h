#pragma once

#include <stdio.h>
#include <stdlib.h>

class BasicDecoder{
	public:
		BasicDecoder();
		virtual ~BasicDecoder();
	
		int getImgWidth();
		int getImgHeight();

		virtual uint8_t* getNextFrame() = 0;
			
		virtual int loadVideo(char* filename) = 0;

	protected:
		int imgWidth;
		int imgHeight;
};

