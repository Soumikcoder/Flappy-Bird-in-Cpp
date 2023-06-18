#include "Bird.hpp"

Bird::Bird(SDL_Texture* p_tex):Entity(216,201,p_tex,2){
	SDL_Rect currentFrame;
	currentFrame.x=294;
	currentFrame.y=242;
	currentFrame.w=20;
	currentFrame.h=14;
	setcurrFrame(currentFrame);
}
void Bird::update(){
	SDL_Rect currentFrame=getFrame();
	currentFrame.x=(((int)(SDL_GetTicks())/speed)%3)*28+294;
	setcurrFrame(currentFrame);
}
