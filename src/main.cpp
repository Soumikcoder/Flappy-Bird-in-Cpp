// Availaible headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include <Cmath>

// user defined headers
#include "RenderWindow.hpp"
#include "Entity.hpp"

//  -m32 doesn't works its 64bit

int main(int argc, char *argv[])
{
	
	// Initializing and Checking for errors in headers
	Init();

	// Intializing game window
	RenderWindow window("GAME",720,640);

	// loading image 
	SDL_Texture* grass=window.loadTexture("res/gfx/ground.png");

	// setting gameloop conditions and events
	bool gamerunning=true;
	SDL_Event event;

	// creating entity

	int pos_x,pos_y;
	std::vector<Entity> entitites;
	entitites.push_back(Entity(60,10,grass,1));
	// int zoom;
	// Game loop
	gametime frames;
	while (gamerunning){
		frames.tick(60);
		while (SDL_PollEvent(&event))
		{

			// Uint64 start=SDL_GetPerformanceCounter();

			SDL_GetMouseState(&pos_x,&pos_y);
			switch (event.type)
			{
				case SDL_QUIT:
					gamerunning=false;
					break;
				case SDL_MOUSEWHEEL :
					if (event.wheel.y>0)
					{
						entitites[entitites.size()-1].increaseZoom();
					}
					else if (event.wheel.y<0)
					{
						entitites[entitites.size()-1].decreaseZoom();
					}
					// zoom=entitites[0]
					break;
				case SDL_MOUSEBUTTONDOWN:
					entitites.push_back(Entity(pos_x-(entitites[entitites.size()-1].getFrame().h*entitites[entitites.size()-1].getZoom()/2),pos_y-(entitites[entitites.size()-1].getFrame().w*entitites[entitites.size()-1].getZoom()/2),grass,entitites[entitites.size()-1].getZoom()));
					if (entitites.size()>10)
					{
						// printf("..........................\n");
						entitites.erase(entitites.begin());
					}
					printf("%lld\n",sizeof(entitites));
					break;
				default:
					break;
			}
			window.clear();
			entitites[entitites.size()-1].setXY(pos_x-(entitites[entitites.size()-1].getFrame().h*entitites[entitites.size()-1].getZoom()/2),pos_y-(entitites[entitites.size()-1].getFrame().w*entitites[entitites.size()-1].getZoom()/2),entitites[entitites.size()-1].getZoom());

			for (unsigned i = 0; i < entitites.size(); ++i)
			{
				window.render(entitites[i]);
			}
			window.display();

			// Uint64 end=SDL_GetPerformanceCounter();

			// float elapsed=(end-start)/(float)SDL_GetPerformanceFrequency()*1000.0f;
			// SDL_Delay(floor(16.666f-elapsed));
		}
	}

	// clearing memory ocuupied by window
	window.cleanup();
	SDL_Quit();
	return 0;
}
