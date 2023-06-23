#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// detailed description of different methods of entity
Entity::Entity(float p_x,float p_y,SDL_Texture* p_tex,float p_zoom=1){
	printf("Entity created\n");
	x=p_x;
	y=p_y;
	tex=p_tex;
	zoom=p_zoom;
}
// accessing all entity members
float Entity::getX(){
	return x;
}
void Entity::setcurrFrame(int pos_x,int pos_y,int width ,int height){
	currentFrame.x=pos_x;
	currentFrame.y=pos_y;
	currentFrame.w=width;
	currentFrame.h=height;
}
void Entity::setcurrFrame(SDL_Rect &stcurrentFrame){
	currentFrame.x=stcurrentFrame.x;
	currentFrame.y=stcurrentFrame.y;
	currentFrame.w=stcurrentFrame.w;
	currentFrame.h=stcurrentFrame.h;
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