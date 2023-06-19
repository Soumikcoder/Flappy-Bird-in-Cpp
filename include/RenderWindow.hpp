#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <Cmath>
#include <cstdio>

#include "Entity.hpp"
#include "Pipe.hpp"
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>

void Init();


class gametime
{
	Uint64 start;
	double elapsed;
public:
	gametime(){
		printf("Frames created\n");
		start=SDL_GetPerformanceCounter();
	}
	double tick(int fps=60){
		Uint64 end=SDL_GetPerformanceCounter();

		elapsed=(end-start)/(double)SDL_GetPerformanceFrequency()*1000.0f;

		if(elapsed<((double)1000.0/fps))
		SDL_Delay(floor(((double)1000.0/fps)-elapsed));

		end=SDL_GetPerformanceCounter();
		elapsed=(end-start)/(double)SDL_GetPerformanceFrequency()*1000.0f;

		start=SDL_GetPerformanceCounter();
		return ((double)1000.0/elapsed);
	}
	float get_elapsed(){
		return elapsed;
	}
};
// Creating window and methods
class RenderWindow
{
	SDL_Renderer *renderer=NULL;
	SDL_Window *window=NULL;
	TTF_Font* Sans = NULL;
	SDL_Texture* Message=NULL;
	SDL_Surface* surfaceMessage=NULL;
public:
	RenderWindow(const char* p_title,int p_w,int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void render(Entity& p_entity,float angle);
	void render_pipe(Pipe& p_entity,int x);
	void render(Entity& p_entity,int x,int y);
	void rendertext(char* text,SDL_Color &color,int x,int y,int height,int width);
	void display();
	void clear();
	void cleanup();
	void update_frames(gametime frames);
};
