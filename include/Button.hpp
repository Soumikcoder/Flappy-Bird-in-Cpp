#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include "RenderWindow.hpp"

class Button
{
	int x;
	int y;
	int height;
	int width;
public:
	Button(int pos_x,int pos_y,int btn_width,int btn_height){
		x=pos_x;
		y=pos_y;
		height=btn_height;
		width=btn_width;
	}
	void glow(RenderWindow window){
		// {241, 121,93}
		SDL_Rect frame;
		frame.x=x-1;
		frame.y=y-1;
		frame.w=(width*2+2);
		frame.h=height*2+2;
		SDL_RenderDrawRect(window.get_renderer(),&frame);
		SDL_SetRenderDrawColor(window.get_renderer(),200,100,1,100);
		
		frame.x=x-2;
		frame.y=y-2;
		frame.w=(width*2+4);
		frame.h=height*2+4;
		SDL_RenderDrawRect(window.get_renderer(),&frame);
		SDL_SetRenderDrawColor(window.get_renderer(),255,0,0,255);
	}
	bool hover(){
		int pos_x,pos_y;
		SDL_GetMouseState(&pos_x,&pos_y);
		if(( pos_y>=y &&pos_y<=y+2*height)&&(pos_x>=x&&pos_x<=2*width+x))
			return true;
		else 
			return false;
	}
};