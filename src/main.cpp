// Availaible headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <vector>
// user defined headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Bird.hpp"
#include "Background.hpp"

#define HEIGHT 432
#define WIDTH 450

//  -m32 doesn't works its 64bit

// this is the color in rgb format,
// maxing out all would give you the color white,
// and it will be your text's color
// as TTF_RenderText_Solid could only be used on
// SDL_Surface then you have to create the surface first

// now you can convert it into a texture
int pos=0;
int main(int argc, char *argv[])
{
	// Initializing and Checking for errors in headers
	Init();

	// Intializing game window
	RenderWindow window("GAME",WIDTH,HEIGHT);

	// loading image 
	SDL_Texture* bg=window.loadTexture("res/gfx/assets.png");

	// setting gameloop conditions and events
	bool gamerunning=true;
	SDL_Event event;

	// creating entity
	Background background1(bg,0);
	Background background2(bg,1);
	Bird flappy(bg);
	// Game loop
	gametime frames;
	while (gamerunning){
		while (SDL_PollEvent(&event))
		{
			window.clear();
			switch (event.type)
			{
				case SDL_QUIT:
					gamerunning=false;
					break;
				case SDL_MOUSEWHEEL :
					break;
				case SDL_MOUSEBUTTONDOWN:
					background1.change_mode();
					break;
				default:
					break;
			}
		}
			draw_background(background1,background2,window,pos);
			flappy.update();
			window.render(flappy);
			frames.tick(60);
			window.update_frames(frames);
			window.display();
			pos++;
	}
	// clearing memory ocuupied by window
	window.cleanup();
	SDL_Quit();
	return 0;
}
