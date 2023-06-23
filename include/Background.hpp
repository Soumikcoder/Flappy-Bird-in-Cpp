#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cstdio>
#include <cstdlib>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Bird.hpp"
#include "Pipe.hpp"
#include "Button.hpp"


class Background:public Entity
{
	int mode;
	SDL_Rect currentFrame;
public:
	 Background(SDL_Texture* p_tex,int mode):Entity(0,0,p_tex,2){
	 	printf("Background created\n");
	 	if(mode){
	 	currentFrame.x=0;
		currentFrame.y=50;
		currentFrame.w=140;
		currentFrame.h=166;
	 	
	 	}
	 	else{
	 	currentFrame.x=300;
		currentFrame.y=0;
		currentFrame.w=60;
		currentFrame.h=55;
		// increaseZoom();
	 	}
	 	if(mode==2) {currentFrame.y=0;
	 	currentFrame.h=216;
	 	}
		setcurrFrame(currentFrame);
	 }
	void change_mode(){
		currentFrame=getFrame();
		currentFrame.x=((currentFrame.x==0)?(147+currentFrame.x):(currentFrame.x-147));
		setcurrFrame(currentFrame);
	}
	
	
};


void draw_background(Background &background1,Background &background2,RenderWindow &window,int pos);
int gameplay(RenderWindow &window,SDL_Texture* bg,Mix_Chunk* flapping_sound,Mix_Chunk* die_sound,Mix_Chunk* hit_sound,Mix_Chunk* point_sound,int &highscore);
int retry(RenderWindow &window,int score,SDL_Texture* bg,int &highscore);
int main_menu(RenderWindow &window,SDL_Texture* bg);