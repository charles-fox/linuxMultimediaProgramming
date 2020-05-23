//from lazyfoo productions lesson 01
//g++ test.cpp -lSDL

#include "SDL/SDL.h"

int main( int argc, char* args[] )
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* hello = NULL;
	hello = SDL_LoadBMP( "hello.bmp" );
	
	SDL_Surface* screen = NULL;
    	//screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE  );
    	screen = SDL_SetVideoMode( 1000, 480, 32, SDL_SWSURFACE );

	


	SDL_BlitSurface( hello, NULL, screen, NULL );
	
	SDL_Flip( screen );
	
	SDL_Delay( 2000 );
	SDL_FreeSurface( hello );
	SDL_Quit();	
	return 0;
}
