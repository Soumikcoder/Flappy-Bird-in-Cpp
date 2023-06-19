#include "Background.hpp"

void draw_background(Background &background1,Background &background2,RenderWindow &window,int pos){
	for(int i=0;i<3;i++){
		window.render(background1,i*280-(pos%280),0);
	}
	for(int i=0;i<6;i++){
		window.render(background2,i*120-(pos%120),332);
	}
	return;
}

int gameplay(RenderWindow &window,SDL_Texture* bg,Mix_Chunk* flapping_sound,Mix_Chunk* die_sound,Mix_Chunk* hit_sound){
	SDL_Color White = {255, 255, 255};
	bool gamerunning=true;
	int pos=0;
	int level=1;
	SDL_Event event;
	int score=0;
	char score_txt[20];
	// creating entity
	Background background1(bg,0);
	Background background2(bg,1);
	Bird flappy(bg);
	std::vector<Pipe> p;
	for(int i=0;i<4;i++){
	p.push_back(Pipe(bg,500+200*i));
	}
	// Game loop
	gametime frames;
	while (gamerunning){
		window.clear();
		while (SDL_PollEvent(&event))
		{
			
			switch (event.type)
			{
				case SDL_QUIT:
					gamerunning=false;
					break;
				case SDL_MOUSEWHEEL :
					break;
				case SDL_MOUSEBUTTONDOWN:
					flappy.flap(frames.get_elapsed());
					Mix_PlayChannel(-1,flapping_sound,0);
					break;
				default:
					break;
				}
			}
			
			if(pos%10000==731){
				background1.change_mode();
				flappy.change_mode();
				level++;
			}
			draw_background(background1,background2,window,pos);
			window.render(flappy,flappy.get_angle(frames.get_elapsed()));
			check_pipe(p,pos);
			for(int i=0;i<4;i++){
			window.render_pipe(p[i],pos);
			}
			frames.tick(60);
			window.update_frames(frames);
			if(crossed_pipe(p,pos,frames.get_elapsed(),level)) score++;
			snprintf(score_txt,sizeof(score_txt),"Score: %d",score);
			window.rendertext(score_txt,White,40,10,20,80);
			if(!flappy.check_colision(p,pos)){
				pos+=((int)frames.get_elapsed()/10*level);
				flappy.update(frames.get_elapsed());
			}
			else{
				Mix_PlayChannel(-1,hit_sound,0);
				Mix_PlayChannel(-1,die_sound,0);
				retry(window,score,bg);
				return 2;
			}
			window.display();

	}
	return 0;
}

int retry(RenderWindow &window,int score,SDL_Texture* bg){
	Entity gameover((225-102),(216-120),bg,2);
	SDL_Rect currentFrame;
	currentFrame.x=390;
	currentFrame.y=58;
	currentFrame.w=102;
	currentFrame.h=24;
	gameover.setcurrFrame(currentFrame);
	window.render(gameover,0);
	Entity scoreboard((225-102),(216-50),bg,2);
	currentFrame.y=180;
	currentFrame.x=397;
	currentFrame.w=(510-397);
	currentFrame.h=(238-180);
	scoreboard.setcurrFrame(currentFrame);
	window.render(scoreboard,0);
	Entity medal((225-102+26),(216-50+42),bg,2);
	currentFrame.x=290;
	currentFrame.y=197;
	currentFrame.w=(313-290);
	currentFrame.h=(220-197);
	medal.setcurrFrame(currentFrame);
	window.render(medal,0);
	// Entity menu((225-102+26),(216-50+42),bg,2);
	// currentFrame.x=290;
	// currentFrame.y=197;
	// currentFrame.w=(313-290);
	// currentFrame.h=(220-197);
	// medal.setcurrFrame(currentFrame);
	// window.render(medal,0);
	window.display();
	SDL_Delay(500);
	return 1;
}