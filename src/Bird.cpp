#include "Bird.hpp"

Bird::Bird(SDL_Texture* p_tex):Entity(216,201,p_tex,2){
	printf("Bird created\n");
	SDL_Rect currentFrame;
	currentFrame.x=294;
	currentFrame.y=242;
	currentFrame.w=width/2;
	currentFrame.h=height/2;
	setcurrFrame(currentFrame);
}
void Bird::update(float elapsed_time){
	velocity-=(2*gravity*elapsed_time/100);
	SDL_Rect currentFrame=getFrame();
	currentFrame.x=(((int)(SDL_GetTicks())/speed)%3)*28+mode_x;
	setcurrFrame(currentFrame);
	float y=getY();
	y+=(-velocity*elapsed_time)/1000;
	setXY(getX(),y,getZoom());
	return;
}
float Bird::get_angle(float elapsed_time){
	float angle=(velocity*elapsed_time)/1000*20;
	return -angle;
}
void Bird::change_mode(){
		mode_x=((mode_x==294)?(168+mode_x):(mode_x-168));
}
void Bird::flap(float elapsed_time){
	velocity=(2*60*gravity*elapsed_time/100);
}

bool Bird::check_colision(std::vector<Pipe> &pipes,int offset){
	if(getY()>=300||getY()<=0)
		return true;
	for(auto &pipe : pipes){
		if(((double)(pipe.getX()-offset)<=(double)(this->getX()+this->width))&&((double)(pipe.getX()-offset+pipe.get_width())>=(double)(this->getX()))){
			if((getY()<=(pipe.getY()-pipe.get_height()))||((getY()+this->height)>=(pipe.getY()+pipe.get_height()))){
			return true;
			}
		}
	}
	return false;
}