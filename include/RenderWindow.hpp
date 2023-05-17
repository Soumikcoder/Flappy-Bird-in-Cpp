#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>


#include "Entity.hpp"
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>

void Init();


class gametime
{
	double lasttime;
public:
	gametime(){
		lasttime=clock();
	}
	void tick(int fps=60){
		while((clock()-lasttime)<(CLOCKS_PER_SEC/(double)fps));
		lasttime=clock();
	}
	
};
// Creating window and methods
class RenderWindow
{
	SDL_Renderer *renderer=NULL;
	SDL_Window *window=NULL;
	TTF_Font* Sans = NULL;
public:
	RenderWindow(const char* p_title,int p_w,int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void render(Entity& p_entity);
	void rendertext(char* text,SDL_Color &color,int x,int y,int height,int width);
	void display();
	void clear();
	void cleanup();
};