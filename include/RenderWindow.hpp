#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>

void Init();

// Creating window and methods
class RenderWindow
{
	SDL_Renderer *renderer=NULL;
	SDL_Window *window=NULL;
public:
	RenderWindow(const char* p_title,int p_w,int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void render(Entity& p_entity);
	void display();
	void clear();
	void cleanup();
};