#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <vector>

class Pipe:public Entity
{
	float pos_x,pos_y;
	int pipe_height=90;
public:
	Pipe(SDL_Texture* p_tex,float x);
	int get_height() {return pipe_height;}
};

void check_pipe(std::vector<Pipe> &pipes,int offset);
bool crossed_pipe(std::vector<Pipe> &pipes,int offset,float elapsed_time,int level);