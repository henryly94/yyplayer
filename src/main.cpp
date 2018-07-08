#include <iostream>
#include "utils.hpp"
#include "toyRenderer.h"
#include "BasicDecoder.h"

int main(int argc, char* argv[]){
	if (argc != 2){
		return -1;
	}	
	std::cout << "Hello World" << std::endl;
	print();
	
	toyRenderer* t = new toyRenderer();
	BasicDecoder d;
	d.loadVideo(argv[1]);
	t->init();
	t->setDecoder(&d);
	t->mainloop();
	t->quit();
	return 0;
}
