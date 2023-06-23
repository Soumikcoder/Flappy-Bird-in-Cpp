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
	// Game loop
	gametime frames;
	Button main_menu((225-18),2*26+(216-50+42+80),40,14);
	Button ok((225-18),2*42+(216-50+42+80),40,13);
	while (gamerunning){
		window.clear();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					gamerunning=false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(!gameover){
					flappy.flap(frames.get_elapsed());
					Mix_PlayChannel(-1,flapping_sound,0);
					}
					else{
						if(main_menu.hover()||ok.hover())
						result=1;
					}
					break;
				case SDL_KEYDOWN:
					if(!gameover){
						if(event.key.keysym.sym==SDLK_UP ||event.key.keysym.sym==SDLK_SPACE||event.key.keysym.sym==SDLK_w){	
							flappy.flap(frames.get_elapsed());
							Mix_PlayChannel(-1,flapping_sound,0);
						}
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
			if(main_menu.hover()) main_menu.glow(window);
			else if(ok.hover()) ok.glow(window);
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
	gameover.setcurrFrame(390,58,102,24);

	Entity scoreboard((225-102),(216-50),bg,2);
	scoreboard.setcurrFrame(397,180,(510-397),(238-180));
	
	Entity medal((225-102+26),(216-50+42),bg,2);
	medal.setcurrFrame((score>10?336:(score>5?313:290)),197,(313-290),(220-197));
	
	Entity menu((225-22),(216-50+42+80),bg,2);
	menu.setcurrFrame(460,0,(505-460),55);

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
	gametime frames;
	SDL_Event event;
	int pos=0;
	bool animation =true;
	Entity menu((225-97),(216-95),bg,2);
	menu.setcurrFrame(291,60,(388-291),155-60);
	
	Button start((225-97),2*31+(216-97),60,50);
	Button share((225-97)+2,2*82+(216-95),40,13);
	Button play((225-97+2*43),2*82+(216-95),13,13);
	Button pause((225-97+2*44+28),2*82+(216-95),13,13);

	while (gamerunning){
		window.clear();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					gamerunning=false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(start.hover())		return 1;
					else if(play.hover())		animation=true;
					else if(pause.hover())	animation=false;
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
			if(play.hover()) play.glow(window);
			else if(pause.hover()) pause.glow(window);
			else if(share.hover()) share.glow(window);
			// else if(start.hover()) start.glow(window);
			window.display();
			if(animation)
			pos+=((int)frames.get_elapsed()/10);
	}
	return 0;
}