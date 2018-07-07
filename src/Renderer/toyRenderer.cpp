#include "toyRenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std::chrono;

toyRenderer::toyRenderer(){
	imgWidth = 640;
	imgHeight = 480;
	counter = 0;
	fps = 60.0;
	last_frame_time = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();

	vertex_shader = 
		"#version 330\n"
		"\n"
		"layout (location=0) in vec3 position;\n"
		"layout (location=1) in vec2 texCoord;\n"
		"\n"
		"out vec2 outTexCoord;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"	outTexCoord = texCoord;\n"
		"}\n";

	fragment_shader = 
		"#version 330\n"
		"\n"
		"in vec2 texCoord;\n"
		"\n"
		"out vec4 fragColor;\n"
		"\n"
		"uniform sampler2D textureSampler;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	fragColor = texture(textureSampler, textCoord);\n"
		"}\n";
}

void toyRenderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void toyRenderer::init(){
	glfwInit();
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
	mWindow = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!mWindow){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(mWindow, key_callback);
		
	glfwMakeContextCurrent(mWindow);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval(1);
	
	setShaders();
	setTextures();
}

void toyRenderer::update(){
	if (counter % 60 == 0){
		for (int i=0; i< imgWidth; i++){
			for (int j=0; j < imgHeight; j++){
				int base = (i + j*imgWidth) * 4;
				bool flag = ((i / 20) % 2) + ((j / 20) % 2) == 1;
				buffer[base] = flag ? (char)255 : 0;
				buffer[base+1] = flag ? (char)255 : 0;
				buffer[base+2] = flag ? (char)255 : 0;
				buffer[base+3] = 1;
			}
		}
	} else if (counter % 60 == 30){
		for (int i=0; i< imgWidth; i++){
			for (int j=0; j < imgHeight; j++){
				int base = (i + j*imgWidth) * 4;
				bool flag = ((i / 20) % 2) + ((j / 20) % 2) != 1;
				buffer[base] = flag ? (char)255 : 0;
				buffer[base+1] = flag ? (char)255 : 0;
				buffer[base+2] = flag ? (char)255 : 0;
				buffer[base+3] = 1;
			}
		}
	}
	counter ++;
	counter = counter % 60;
}

void toyRenderer::tick(){

	update();
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexSubImage2D(
			GL_TEXTURE_2D,
			0,
			0,
			0,
			imgWidth,
			imgHeight,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			buffer
			);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void toyRenderer::drawframe(){
	glUseProgram(program);
		
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f( 0.0, 0.0 );
    glVertex3f( -1.0, -1.0, 0.0 );

    glTexCoord2f( 0.0, 1.0);
    glVertex3f( -1.0, 1.0, 0.0 );

    glTexCoord2f( 1.0, 1.0);
    glVertex3f( 1.0, 1.0, 0.0 );

    glTexCoord2f( 1.0, 0.0 );
    glVertex3f( 1.0, -1.0, 0.0 );
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE, 0);
	glUseProgram(0);
}

void toyRenderer::mainloop(){
	while (!glfwWindowShouldClose(mWindow)){
		int cur_time = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
		int interval = cur_time - last_frame_time;
		if (interval > (1000.0 / fps)) {
			glfwGetFramebufferSize(mWindow, &width, &height);
			glViewport(0, 0, width, height);	
			glClear(GL_COLOR_BUFFER_BIT);
			tick();
			drawframe();
			glFlush();
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
			last_frame_time = cur_time;		
		}		
	}		
}

void toyRenderer::quit(){
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}


void toyRenderer::setShaders(){
    int vertexShader = glCreateShader( GL_VERTEX_SHADER );
    int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	
    glShaderSource(vertexShader, 1, (const GLchar**)&vertex_shader, NULL);
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragment_shader, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);	
}

void toyRenderer::setTextures(){
	buffer = new char[imgWidth * imgHeight * 4];
			
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);  	
}

/*
	int main(){
		
		toyRenderer*  r;
		r = new toyRenderer();

		r->init();

		r->mainloop();
	
		r->quit();
	
		return 0;
	}
*/
