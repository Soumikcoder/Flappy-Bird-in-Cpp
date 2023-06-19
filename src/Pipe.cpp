#include "Pipe.hpp"
#include <stdlib.h>
#include <cstdio>

Pipe::Pipe(SDL_Texture* p_tex,float x):Entity(216,201,p_tex,2){
	printf("Pipe created\n");
	SDL_Rect currentFrame;
	currentFrame.x=515;
	currentFrame.y=0;
	currentFrame.w=25;
	currentFrame.h=160;
	setcurrFrame(currentFrame);
	setXY(x,60+(rand()%200),1);
}

void check_pipe(std::vector<Pipe> &pipes,int offset){
	for(auto &pipe : pipes){
		// printf("%f\n",(double)(pipe.getX()-offset));
		if((double)(pipe.getX()-offset)<(double)(-200.0)){
			// printf("A\n");
			pipe.setXY((double)(pipe.getX()+200*4),60+(rand()%200),1);
		}
	}
	return;
}

bool crossed_pipe(std::vector<Pipe> &pipes,int offset,float elapsed_time,int level){
	for(auto &pipe : pipes){
		// printf("%f\n",(double)(pipe.getX()-offset));
		if(((double)(pipe.getX()-offset+50)<=(double)(216.0))&&(double)(pipe.getX()-offset+50)>=(double)(216.0-(int)elapsed_time/10*level)){
			// printf("A\n");
			return true;
		}
	}
	return false;
}