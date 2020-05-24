//AR demo using SDL2, GL and CV
//read from the webcam using CV, and use them imgs to draw as GL textures

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

static SDL_Window* window;
static SDL_Renderer* renderer;
static int const screen_size[2] = {800,600};

VideoCapture cap(0); //local webcam
Mat frame;

void init() {
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,800,600,1.0,-1.0,1.0);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void draw(){
	bool b = cap.read(frame);
	imshow("foo2", frame);
	waitKey(30);
/*
	GLuint object;
	glGenTextures(2,&object);
	glBindTexture(GL_TEXTURE_2D,object);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D,0,3,frame.cols,frame.rows,0,GL_BGR,GL_UNSIGNED_BYTE,frame.data);

	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,object);
*/
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(0,0);
	glTexCoord2f(1,0);
	glVertex2f(500,0);
	glTexCoord2f(1,1);
	glVertex2f(500,500);
	glTexCoord2f(0,1);
	glVertex2f(0,500);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING|SDL_INIT_NOPARACHUTE);
    window = SDL_CreateWindow("texture", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, screen_size[0],screen_size[1], SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    glEnable(GL_DEPTH_TEST);
    init();
    while (true) {
    	SDL_Event event;
    	SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) return false;
        draw();
    	SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
