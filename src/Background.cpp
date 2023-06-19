#include "Background.hpp"

void draw_background(Background &background1,Background &background2,RenderWindow &window,int pos,int mode){
	for(int i=0;i<3;i++){
		window.render(background1,i*280-(pos%280),0);
	}
	if(mode){

	for(int i=0;i<6;i++){
		window.render(background2,i*120-(pos%120),332);
	}
	}
	return;
}

int gameplay(RenderWindow &window,SDL_Texture* bg,Mix_Chunk* flapping_sound,Mix_Chunk* die_sound,Mix_Chunk* hit_sound,Mix_Chunk* point_sound,int &highscore){
	SDL_Color White = {255, 255, 255};
	bool gamerunning=true;
	int pos=0;
	int level=1;
	SDL_Event event;
	int score=0;
	char score_txt[20];
	// creating entity
	Background background1(bg,1);
	Background background2(bg,0);
	Bird flappy(bg);
	std::vector<Pipe> p;
	for(int i=0;i<4;i++){
	p.push_back(Pipe(bg,500+200*i));
	}
	bool gameover =false;
	int result=0;
	int pos_x,pos_y;
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
					if(!gameover){
					flappy.flap(frames.get_elapsed());
					Mix_PlayChannel(-1,flapping_sound,0);
					}
					else{
						SDL_GetMouseState(&pos_x,&pos_y);
						if(( pos_y>=2*26+(216-50+42+80) &&pos_y<=(216-50+42+80)+2*39)&&(pos_x>=(225-20)&&pos_x<=2*55+(225-20)))
						result=1;
					}
					break;
				default:
					break;
				}
			}
			

			if(result) return 2;
			if(pos%10000==731){
				background1.change_mode();
				flappy.change_mode();
				level++;
			}
			draw_background(background1,background2,window,pos,1);
			window.render(flappy,flappy.get_angle(frames.get_elapsed()));
			check_pipe(p,pos);
			for(int i=0;i<4;i++){
			window.render_pipe(p[i],pos);
			}
			frames.tick(60);
			window.update_frames(frames);
			if(gameover){
			retry(window,score,bg,highscore);
			continue;
			} 
			if((!gameover)&&crossed_pipe(p,pos,frames.get_elapsed(),level)) {
				score++;
				Mix_PlayChannel(-1,point_sound,0);
			}
			snprintf(score_txt,sizeof(score_txt),"Score: %d",score);
			window.rendertext(score_txt,White,40,10,20,80);
			if(!gameover&&!flappy.check_colision(p,pos)){
				pos+=((int)frames.get_elapsed()/10*level);
				flappy.update(frames.get_elapsed());
			}
			else{
				gameover=true;
				if(highscore<score)
					highscore=score;
				Mix_PlayChannel(-1,hit_sound,0);
				Mix_PlayChannel(-1,die_sound,0);
				retry(window,score,bg,highscore);
				continue;
			}
			window.display();

	}
	return 0;
}

int retry(RenderWindow &window,int score,SDL_Texture* bg,int &highscore){
	Entity gameover((225-102),(216-120),bg,2);
	SDL_Rect currentFrame;
	currentFrame.x=390;
	currentFrame.y=58;
	currentFrame.w=102;
	currentFrame.h=24;
	gameover.setcurrFrame(currentFrame);

	Entity scoreboard((225-102),(216-50),bg,2);
	currentFrame.y=180;
	currentFrame.x=397;
	currentFrame.w=(510-397);
	currentFrame.h=(238-180);
	scoreboard.setcurrFrame(currentFrame);
	
	Entity medal((225-102+26),(216-50+42),bg,2);
	currentFrame.x=(score>10?336:(score>5?313:290));
	currentFrame.y=197;
	currentFrame.w=(313-290);
	currentFrame.h=(220-197);
	medal.setcurrFrame(currentFrame);
	
	Entity menu((225-22),(216-50+42+80),bg,2);
	 currentFrame.x=460;
	 currentFrame.y=0;
	 currentFrame.w=(505-460);
	 currentFrame.h=55;
	 menu.setcurrFrame(currentFrame);
	window.render(gameover,0);
	window.render(scoreboard,0);
	window.render(medal,0);
	window.render(menu,0);
	char score_txt[20];
	SDL_Color Black = {241, 121,93};
	snprintf(score_txt,sizeof(score_txt),"%d",score);
	window.rendertext(score_txt,Black,2*(486-395)+(225-102),2*(200-182-1)+(216-50),20,15);
	snprintf(score_txt,sizeof(score_txt),"%d",highscore);
	window.rendertext(score_txt,Black,2*(486-395)+(225-102),2*(200-182+24-1)+(216-50),20,15);
	window.display();
	return 1;
}


int main_menu(RenderWindow &window,SDL_Texture* bg){
	Background background1(bg,2);
	bool gamerunning=true;
	int result=0;
	int pos_x,pos_y;
	gametime frames;
	SDL_Event event;
	int pos=0;
	SDL_Rect currentFrame;
	Entity menu((225-97),(216-95),bg,2);
	 currentFrame.x=291;
	 currentFrame.y=60;
	 currentFrame.w=(388-291);
	 currentFrame.h=155-60;
	 bool animation =true;
	 menu.setcurrFrame(currentFrame);
	
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
			
					SDL_GetMouseState(&pos_x,&pos_y);
					if(( pos_y>=2*31+(216-95) &&pos_y<=(216-95)+2*81)&&(pos_x>=(225-97)&&pos_x<=2*60+(225-97)))
						return 1;
					else if(( pos_y>=2*82+(216-95) &&pos_y<=(216-95)+2*95)&&(pos_x>=(225-97+2*43)&&pos_x<=2*55+(225-97))) animation=true;
					else if(( pos_y>=2*82+(216-95) &&pos_y<=(216-95)+2*95)&&(pos_x>=(225-97+2*43+28)&&pos_x<=2*55+(225-97+28)))	animation=false;
					break;
				default:
					break;
				}
			}
			if(result) return 2;
			draw_background(background1,background1,window,pos,0);
			frames.tick(60);
			window.update_frames(frames);
			window.render(menu,0);
			window.display();
			if(animation)
			pos+=((int)frames.get_elapsed()/10);
	}
	return 0;
}