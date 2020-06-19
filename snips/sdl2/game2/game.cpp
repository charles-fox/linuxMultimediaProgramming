#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#include "PhysicalSubstance.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;


void PhysicalSubstance_init(PhysicalSubstance* ps, SDL_Surface* costume) {
	ps->x = 0;
	ps->y = 0;
	ps->dy = 0;
	ps->dy = 0;
	ps->mass = 1;
	ps->costume=costume;
}

void PhysicalSubstance_draw(PhysicalSubstance* ps, SDL_Surface* drawingSurface) {
	SDL_Rect rect;
	rect.x = ps->x;
	rect.y = ps->y;
	rect.w = 100;
	rect.h = 100;
	SDL_BlitSurface(ps->costume,NULL, drawingSurface, &rect );
}

void Cow_step(PhysicalSubstance* cow, PhysicalSubstance* farmer) { 
	int dx = cow->x - farmer->x;
	int dy = cow->y - farmer->y;
	int r = sqrt( pow(dx,2) + pow(dy,2) );
	if (r<100) {
		cow->x += dx/10;
		cow->y += dy/10;
	}
}

int main( int argc, char* args[] )
{
	SDL_Init( SDL_INIT_VIDEO );
	gWindow = SDL_CreateWindow( "Cow game (use cursor keys to move)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	//SDL_SetWindowFullscreen(gWindow, 1);
	gScreenSurface = SDL_GetWindowSurface(gWindow);

	SDL_Surface* penguin1 = SDL_LoadBMP("penguin1.bmp");
	PhysicalSubstance farmer;
	PhysicalSubstance_init(&farmer, penguin1);
	
	SDL_Surface* cow1 = SDL_LoadBMP("cow1.bmp");
	PhysicalSubstance cow;
	PhysicalSubstance_init(&cow, cow1);
	cow.x = 400;
	cow.y = 300;


	bool quit = false;
	SDL_Event e;  
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type==SDL_QUIT) {
				quit=true;
			}
			else if (e.type==SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						farmer.y-=2; break;
					case SDLK_DOWN:
						farmer.y+=2; break;
					case SDLK_LEFT:
						farmer.x-=2; break;
					case SDLK_RIGHT:
						farmer.x+=2; break;
				}
			}
		}

		Cow_step(&cow, &farmer);

		SDL_FillRect(gScreenSurface, NULL, 0x00AA00); //clear screen
	
		PhysicalSubstance_draw(&farmer, gScreenSurface);
		PhysicalSubstance_draw(&cow, gScreenSurface);

		SDL_UpdateWindowSurface(gWindow); //show the surface 
	}

	SDL_FreeSurface(penguin1);
	penguin1 = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
	return 0;
}
