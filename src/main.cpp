// Availaible headers
//SoumikCoder@ or VolatileBits
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

// user defined headers
#include "RenderWindow.hpp"
// #include "Entity.hpp"
// #include "Bird.hpp"
#include "Background.hpp"
// #include "Pipe.hpp"

#define HEIGHT 432
#define WIDTH 450

//  -m32 doesn't works its 64bit

// this is the color in rgb format,
// maxing out all would give you the color white,
// and it will be your text's color
// as TTF_RenderText_Solid could only be used on
// SDL_Surface then you have to create the surface first

// now you can convert it into a texture

int main(int argc, char *argv[])
{
	// Initializing and Checking for errors in headers
	Init();
	srand(time(NULL));
	// Intializing game window
	RenderWindow window("Flappy Bird By Soumik",WIDTH,HEIGHT);

	// loading image 
	SDL_Surface* icon = IMG_Load("res/gfx/icon.png");
	SDL_Texture* bg=window.loadTexture("res/gfx/assets.png");
	 SDL_SetWindowIcon(window.get_window(), icon);
	//constant music
	// Mix_Music* flapping=Mix_LoadMUS("res/sound/sounds_sfx_wing.ogg");
	// Mix_PlayMusic(flapping,0);
	Mix_Chunk* flapping_sound=Mix_LoadWAV("res/sound/sounds_sfx_wing.ogg");
	Mix_Chunk* die_sound=Mix_LoadWAV("res/sound/sounds_sfx_die.ogg");
	Mix_Chunk* hit_sound=Mix_LoadWAV("res/sound/sounds_sfx_hit.ogg");
	Mix_Chunk* point_sound=Mix_LoadWAV("res/sound/sounds_sfx_point.ogg");
	// setting gameloop conditions and events
	int mode=0;
	FILE* fp;
	fp=fopen("res/score.dat","rb");
	int highscore=0;
	if(fp==NULL){
		//file is not generated yet
		fp=fopen("res/score.dat","wb");
		system("attrib +h +s res/score.dat");
	}
	else{
		fread(&highscore,1,sizeof(highscore),fp);
	}
	do{
	mode=main_menu(window,bg);
	if(mode)
	mode=gameplay(window,bg,flapping_sound,die_sound,hit_sound,point_sound,highscore);
	}while(mode);
	fwrite(&highscore,1,sizeof(highscore),fp);
	fclose(fp);
	// clearing memory ocuupied by window
	window.cleanup();
	SDL_Quit();
	return 0;
}
