#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init()
{
	SDL_Init( SDL_INIT_VIDEO );
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	//SDL_SetWindowFullscreen(gWindow, 1);

	gScreenSurface = SDL_GetWindowSurface( gWindow );
}

bool loadMedia()
{
	gHelloWorld = SDL_LoadBMP( "hello.bmp" );
}

void close()
{
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	init();
	loadMedia();
	
	SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface( gWindow );
	SDL_Delay( 2000 );
	
	close();
	return 0;
}
