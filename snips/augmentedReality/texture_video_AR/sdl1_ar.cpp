//render an openCV webcam stream into a 3d openGL object texture

//g++ -std=c++11 -I/opt/ros/kinetic/include/opencv-3.3.1/  test.cpp  /opt/ros/kinetic/lib/libopencv_*.so -L/usr/lib/x86_64-linux-gnu  -lGLU -lGL -lSDL -lSDL_image

#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

using namespace std;
using namespace cv;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

int tex;
VideoCapture cap(0);
Mat frame;

void init(){
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

int main(int argc,char** argv){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen=SDL_SetVideoMode(800,600,32,SDL_SWSURFACE|SDL_OPENGL);
	bool running=true;
	Uint32 start;
	SDL_Event event;
	init();
	if(!cap.isOpened())  // check if we succeeded
	{
		cout << "outch" << endl;
		return -1;
	}
	namedWindow("edges",1);
	while(running)
	{
		start=SDL_GetTicks();
		draw();
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running=false;
				break;
			}
		}
		SDL_GL_SwapBuffers();
		if(1000/60>(SDL_GetTicks()-start))
			SDL_Delay(1000/60-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;
}
