//sudo apt-get install libsdl-image1.2-dev
//g++ test.cpp  -L/usr/lib/x86_64-linux-gnu  -lGLU -lGL -lSDL -lSDL_image

#include "SDL/SDL.h"
    #include "SDL/SDL_opengl.h"
    #include "SDL/SDL_image.h"

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_BPP = 32;

    int tex;

    int loadTexture(char* fileName){

        SDL_Surface *image=IMG_Load(fileName);
        SDL_DisplayFormatAlpha(image);

        GLuint object;
        glGenTextures(1,&object);
        glBindTexture(GL_TEXTURE_2D,object);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->w,image->h,0,GL_RGBA,GL_UNSIGNED_BYTE,image->pixels);

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
        tex = loadTexture("hi.png");
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
    int main(int argc,char** argv){
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Surface* screen=SDL_SetVideoMode(800,600,32,SDL_SWSURFACE|SDL_OPENGL);
        bool running=true;
        Uint32 start;
        SDL_Event event;
        init();
        while(running){
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
