#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include "opencv2/opencv.hpp"
using namespace cv;

static SDL_Window* window;
static SDL_Renderer* renderer;
static int const screen_size[2] = {800,600};
static GLuint texture;

VideoCapture cap(0); //local webcam
Mat frame;
 
static void draw(void) {
    //SDL_Surface* surf = SDL_LoadBMP("texture.bmp");
    bool b = cap.read(frame);
    imshow("foo2", frame);
    waitKey(30);

    GLenum data_fmt = GL_RGB;  //GL_BGR or GL_RGB
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w,surf->h, 0, data_fmt,GL_UNSIGNED_BYTE,surf->pixels);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame.cols,frame.rows, 0, data_fmt,GL_UNSIGNED_BYTE,frame.data);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //SDL_FreeSurface(surf);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,screen_size[0],screen_size[1]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)(screen_size[0])/(double)(screen_size[1]), 0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0,3.0,4.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
 
    glBindTexture(GL_TEXTURE_2D,texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f,0.0f); //All subsequent vertices will have an associated texture coordinate of (0,0)
    glVertex3f( 0.0f, 0.1f, 0.0f);
    glTexCoord2f(1.0f,0.0f); //All subsequent vertices will have an associated texture coordinate of (1,0)
    glVertex3f(-0.1f,-0.1f, 0.7f);
    glTexCoord2f(0.0f,1.0f); //All subsequent vertices will have an associated texture coordinate of (0,1)
    glVertex3f( 1.0f,-0.2f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
 
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING|SDL_INIT_NOPARACHUTE);
    window = SDL_CreateWindow("texture", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, screen_size[0],screen_size[1], SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    glEnable(GL_DEPTH_TEST);
    while (true) {
    	SDL_Event event;
    	SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) return false;
        draw();
    	SDL_GL_SwapWindow(window);
    }
    glDeleteTextures(1,&texture);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
