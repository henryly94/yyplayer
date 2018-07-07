#include <iostream>
#include "utils.hpp"
#include "toyRenderer.h"

int main(){
	
	std::cout << "Hello World" << std::endl;
	print();
	
	toyRenderer* t = new toyRenderer();

	t->init();
	t->mainloop();
	t->quit();
	return 0;
}
