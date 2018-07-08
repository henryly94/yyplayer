#include "BasicDecoder.h"


BasicDecoder::BasicDecoder(){
	imgWidth = 0;
	imgHeight = 0;
}

BasicDecoder::~BasicDecoder(){

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
