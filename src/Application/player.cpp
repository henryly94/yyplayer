#include <iostream>
#include "utils.hpp"
#include "toyRenderer.h"
#include "BasicDecoder.h"
#include "FFmpegDecoder.h"

int main(int argc, char* argv[]){
	if (argc != 2){
		return -1;
	}	
	std::cout << "Hello World" << std::endl;
	print();
	
	toyRenderer* t = new toyRenderer();
	FFmpegDecoder d;
	d.loadVideo(argv[1]);
	t->init();
	t->setDecoder((BasicDecoder*)&d);
	t->mainloop();
	t->quit();
	return 0;
}
