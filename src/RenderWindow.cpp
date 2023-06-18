#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>


// detailed description of all methods of window
RenderWindow::RenderWindow(const char* p_title,int p_w,int p_h)
{
	printf("RenderWindow created\n");
	window=SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Failed to open %d x %d window: %s\n", p_w, p_h, SDL_GetError());
		exit(1);
	}
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	Sans = TTF_OpenFont("res/font/font.ttf",60);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
	SDL_Texture* texture=NULL;
	texture=IMG_LoadTexture(renderer,p_filePath);
	if (texture==NULL)
	{
			printf("failure to load texture :%s\n",SDL_GetError() );
	}
	return texture;
}

void RenderWindow::render(Entity& p_entity,float angle){
	SDL_Rect src;
	src.x=p_entity.getFrame().x;
	src.y=p_entity.getFrame().y;
	src.h=p_entity.getFrame().h;
	src.w=p_entity.getFrame().w;

	SDL_Rect dst;
	dst.x=p_entity.getX();
	dst.y=p_entity.getY();
	dst.w=p_entity.getFrame().w*p_entity.getZoom();
	dst.h=p_entity.getFrame().h*p_entity.getZoom();

	SDL_RenderCopyEx(renderer,p_entity.getTex(),&src,&dst,angle,NULL,SDL_FLIP_NONE);
	return;
}
void RenderWindow::render_pipe(Entity& p_entity,int offset){
	SDL_Rect src;
	src.x=p_entity.getFrame().x-1;
	src.y=p_entity.getFrame().y;
	src.h=p_entity.getFrame().h;
	src.w=p_entity.getFrame().w+1;

	SDL_Rect dst;
	dst.x=p_entity.getX()-offset;
	dst.y=0;
	dst.w=(p_entity.getFrame().w*p_entity.getZoom())*2;
	dst.h=p_entity.getY()-40;

	SDL_RenderCopy(renderer,p_entity.getTex(),&src,&dst);
	src.x=p_entity.getFrame().x+27;
	src.y=p_entity.getFrame().y;
	src.h=p_entity.getFrame().h;
	src.w=p_entity.getFrame().w+2;

	dst.x=p_entity.getX()-2-offset;
	dst.y=p_entity.getY()+40;
	dst.w=(p_entity.getFrame().w*p_entity.getZoom())*2;
	dst.h=332-p_entity.getY()-40;
	SDL_RenderCopy(renderer,p_entity.getTex(),&src,&dst);
	return;
}
void RenderWindow::render(Entity& p_entity,int x,int y){
	SDL_Rect src;
	src.x=p_entity.getFrame().x;
	src.y=p_entity.getFrame().y;
	src.h=p_entity.getFrame().h;
	src.w=p_entity.getFrame().w;

	SDL_Rect dst;
	dst.x=x;
	dst.y=y;
	dst.w=p_entity.getFrame().w*p_entity.getZoom();
	dst.h=p_entity.getFrame().h*p_entity.getZoom();

	SDL_RenderCopy(renderer,p_entity.getTex(),&src,&dst);
}

void RenderWindow::rendertext(char* text,SDL_Color &color,int x,int y,int height,int width){
	surfaceMessage =TTF_RenderText_Solid(Sans, text, color); 
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_Rect src;
	src.x=x;
	src.y=y;
	src.h=height;
	src.w=width;
	SDL_RenderCopy(renderer,Message,NULL,&src);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void RenderWindow::display(){
	SDL_RenderPresent(renderer);

	return;
}


void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}



void RenderWindow::cleanup(){
	SDL_DestroyWindow(window);
}


void Init(void){
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	if (!IMG_Init(IMG_INIT_PNG))		
	{
		printf("Image failed!");
	}
	if(TTF_Init()==-1){
		printf("Fonts failed!");
	}
	// if (Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)
	// {
	// 	printf("Image failed!");
	// }
}

void RenderWindow::update_frames(gametime frames){
	char fps[10];
	SDL_Color White = {255, 255, 255};
	snprintf(fps,sizeof("FPS:100.00"),"FPS:%.2lf",frames.tick(60));
	rendertext(fps,White,215,10,20,80);
	return;
}