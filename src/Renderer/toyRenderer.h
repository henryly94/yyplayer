#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <BasicDecoder.h>

class toyRenderer{

private:
	GLFWwindow* mWindow;
	
	int width;
	int height;

	double fps;
	int last_frame_time;
	int imgWidth;
	int imgHeight;
	int counter;		
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void drawframe();

	const GLchar* vertex_shader;
	const GLchar* fragment_shader;
	
	int program;
	unsigned int texture;

	void setShaders();

	void setTextures();

	uint8_t* buffer;
	
	void update();
	void tick();

	BasicDecoder* mDecoder;

public:

	toyRenderer();
	
	~toyRenderer();
	
	void setDecoder(BasicDecoder* decoder);	

	void init();

	void mainloop();
			
	void quit();
	
};
