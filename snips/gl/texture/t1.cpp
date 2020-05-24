#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "SDL2/SDL_image.h"
#include <GL/glu.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* gWindow = NULL;
SDL_GLContext gGlContext;
const int SCREEN_BPP = 32;
int tex;

int loadTexture(char* fileName){
	SDL_Surface *image=IMG_Load(fileName);  //from SDL_image library (also in SDL2)
	//SDL_DisplayFormatAlpha(image); //SDL1

	GLuint object;
	glGenTextures(1,&object);
	glBindTexture(GL_TEXTURE_2D,object);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	printf("f\n");
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->w,image->h,0,GL_RGBA,GL_UNSIGNED_BYTE,image->pixels); //TODO error SDL2
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->w,image->h,0,GL_RGB,GL_UNSIGNED_BYTE,image->pixels); //TODO error SDL2
	printf("c\n");
	SDL_FreeSurface(image);
	return object;
}

void init(){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,800,600,1.0,-1.0,1.0);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	tex = loadTexture("hello.bmp");
}

int setViewport(int width, int height) {
    GLfloat ratio;
    if (height == 0) {
        height = 1;
    }
    ratio = GLfloat(width) / GLfloat(height);
    glViewport(0, 0, GLsizei(width), GLsizei(height));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return true;
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,tex);
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

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Opengl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	gGlContext = SDL_GL_CreateContext(gWindow);
	init();
	setViewport(SCREEN_WIDTH, SCREEN_HEIGHT);
	bool quit = false;
	SDL_Event sdlEvent;
	while (!quit) {
		while (SDL_PollEvent(&sdlEvent) != 0) {
		    if (sdlEvent.type == SDL_QUIT) {
			quit = true;
		    }
		}
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
		SDL_GL_SwapWindow(gWindow);
	}
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
	return 0;
}   
