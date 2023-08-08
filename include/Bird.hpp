#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <vector>

#include "Pipe.hpp"
class Bird:public Entity
{
	float velocity;
	float gravity=9.8;
	int speed=150;
	float mode_x=294;
public:
	int width=40;
	int height=28;
	Bird(SDL_Texture* p_tex);
	void update(float elapsed_time);
	void change_mode();
	float get_angle();
	void flap();
	bool check_colision(std::vector<Pipe> &pipes,int offset);
};
