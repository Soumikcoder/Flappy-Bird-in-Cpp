#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>

class Background:public Entity
{
	int mode;
	SDL_Rect currentFrame;
public:
	 Background(SDL_Texture* p_tex,int mode):Entity(0,0,p_tex,2){
	 	if(mode){
	 	currentFrame.x=300;
		currentFrame.y=0;
		currentFrame.w=60;
		currentFrame.h=55;
	 	}
	 	else{
	 	currentFrame.x=0;
		currentFrame.y=50;
		currentFrame.w=140;
		currentFrame.h=166;
		// increaseZoom();
	 	}
		setcurrFrame(currentFrame);
	 }
	void change_mode(){
		currentFrame=getFrame();
		currentFrame.x=((currentFrame.x==0)?(147+currentFrame.x):(currentFrame.x-147));
		setcurrFrame(currentFrame);
	}
	
	
};


void draw_background(Background& background1,Background& background2,RenderWindow& window,int pos){
	for(int i=0;i<3;i++){
		window.render(background1,i*280-(pos%280),0);
	}
	for(int i=0;i<6;i++){
		window.render(background2,i*120-(pos%120),332);
	}

}