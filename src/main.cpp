// Availaible headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
// user defined headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Bird.hpp"
#include "Background.hpp"
#include "Pipe.hpp"

#define HEIGHT 432
#define WIDTH 450

//  -m32 doesn't works its 64bit

// this is the color in rgb format,
// maxing out all would give you the color white,
// and it will be your text's color
// as TTF_RenderText_Solid could only be used on
// SDL_Surface then you have to create the surface first

// now you can convert it into a texture

int main(int argc, char *argv[])
{
	// Initializing and Checking for errors in headers
	Init();
	srand(time(NULL));
	// Intializing game window
	RenderWindow window("GAME",WIDTH,HEIGHT);

	// loading image 
	int pos=0;
	int level=1;
	SDL_Texture* bg=window.loadTexture("res/gfx/assets.png");
	// setting gameloop conditions and events
	bool gamerunning=true;
	SDL_Event event;

	// creating entity
	Background background1(bg,0);
	Background background2(bg,1);
	Bird flappy(bg);
	std::vector<Pipe> p;
	for(int i=0;i<4;i++){
	p.push_back(Pipe(bg,500+200*i));
	}
	// Game loop
	gametime frames;
	while (gamerunning){
		window.clear();
		while (SDL_PollEvent(&event))
		{
			
			switch (event.type)
			{
				case SDL_QUIT:
					gamerunning=false;
					break;
				case SDL_MOUSEWHEEL :
					break;
				case SDL_MOUSEBUTTONDOWN:
					flappy.flap(frames.get_elapsed());
					break;
				default:
					break;
				}
			}
			if(!flappy.check_colision(p,pos)){
				pos+=((int)frames.get_elapsed()/10*level);
				flappy.update(frames.get_elapsed());
			}
			if(pos%10000==531){
				background1.change_mode();
				flappy.change_mode();
			}
			draw_background(background1,background2,window,pos);
			
			window.render(flappy,flappy.get_angle(frames.get_elapsed()));
			check_pipe(p,pos);
			for(int i=0;i<4;i++){
			window.render_pipe(p[i],pos);
			}
			frames.tick(60);
			window.update_frames(frames);
			window.display();

	}
	// clearing memory ocuupied by window
	window.cleanup();
	SDL_Quit();
	return 0;
}
