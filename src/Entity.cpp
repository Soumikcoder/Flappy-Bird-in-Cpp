#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// detailed description of different methods of entity
Entity::Entity(float p_x,float p_y,SDL_Texture* p_tex,float p_zoom=1){
	x=p_x;
	y=p_y;
	tex=p_tex;
	zoom=p_zoom;
	currentFrame.x=0;
	currentFrame.y=0;
	currentFrame.w=128;
	currentFrame.h=128;
}
// accessing all entity members
float Entity::getX(){
	return x;
}

float Entity::getY(){
	return y;
}
float Entity::getZoom(){
	return zoom;
}

void Entity::increaseZoom(){
	zoom+=0.1;
}

void Entity::decreaseZoom(){
	zoom=(zoom>0?zoom-.1:zoom);
}

SDL_Texture* Entity::getTex(){
	return tex;
}

SDL_Rect Entity::getFrame(){
	return currentFrame;
}
// setting entity position
void Entity::setXY(float p_x,float p_y,float p_zoom){
	x=p_x;
	y=p_y;
	zoom=p_zoom;
}