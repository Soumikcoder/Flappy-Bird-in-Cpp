#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>

class Bird:public Entity
{
	float velocity;
	float gravity=9.8;
	int speed=150;
public:
	Bird(SDL_Texture* p_tex);
	void update();
};