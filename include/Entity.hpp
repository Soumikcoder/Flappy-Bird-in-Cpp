#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>

// creating Entity and declearing different methods
class Entity
{
	float x,y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	float zoom;
public:
	Entity(float p_x,float p_y,SDL_Texture* p_tex,float p_zoom);
	float getX();
	float getY();
	float getZoom();
	void increaseZoom();
	void decreaseZoom();
	void setcurrFrame(int pos_x,int pos_y,int width ,int height);
	void setcurrFrame(SDL_Rect &stcurrentFrame);
	void setXY(float p_x,float p_y,float p_zoom);
	SDL_Texture* getTex();
	SDL_Rect getFrame();
};