#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* penguin1 = NULL;

int main( int argc, char* args[] )
{
	SDL_Init( SDL_INIT_VIDEO );
	gWindow = SDL_CreateWindow( "SDL game (use cursor keys to move)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	//SDL_SetWindowFullscreen(gWindow, 1);
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	penguin1 = SDL_LoadBMP("penguin1.bmp");

	bool quit = false;
	SDL_Event e;  
	int x=0; int y=0;
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type==SDL_QUIT) {
				quit=true;
			}
			else if (e.type==SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						y-=1; break;
					case SDLK_DOWN:
						y+=1; break;
					case SDLK_LEFT:
						x-=1; break;
					case SDLK_RIGHT:
						x+=1; break;
				}
			}
		}
		printf("%i, %i\n", x, y);
		SDL_FillRect(gScreenSurface, NULL, 0x000000); //clear screen
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = 100;
		rect.h = 100;
		SDL_BlitSurface(penguin1,NULL, gScreenSurface, &rect );
		SDL_UpdateWindowSurface(gWindow); //show the surface 
	}

	SDL_FreeSurface(penguin1);
	penguin1 = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
	return 0;
}
