//g++ testSDL2.cpp -lSDL2
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

int main( int argc, char* args[] )
{
	SDL_Init( SDL_INIT_VIDEO );
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	//SDL_SetWindowFullscreen(gWindow, 1);
	gScreenSurface = SDL_GetWindowSurface( gWindow );

	gHelloWorld = SDL_LoadBMP( "hello.bmp" );
	SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface( gWindow );
	SDL_Delay( 2000 );
	
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	SDL_Quit();
	return 0;
}
