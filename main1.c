#include "menu.h"
int main()
{
/*****DECLARATION DES VARIABLE*****/

	//etat

	int menu =0,set = 1 ;
	//fenetre

	SDL_Surface* screen ; 
	
	//variable du boucle

	int boucle = 1 ,select=1;

	//variable d'evenement
	
	SDL_Event event ;
	
	//background
	
	background back_menu , back_setting  ;
	
	//les bouton
	
	bouton volum_up , volum_down ,fullscreen ,retour1,mute;
	//son

	Mix_Music *musique;
	Mix_Chunk *song_bref;
	int volum=10;
	//text
	
	text txt_menu;

/*****INITIALISATION DES VARIABLE*****/

	TTF_Init();
	screen = SDL_SetVideoMode (1070 ,675 ,32,SDL_HWSURFACE|SDL_SRCALPHA);
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	//Menu
	initialiser_backmenu(&back_menu);
	//Play


	//Settings
        
	initialiser_backsetting(&back_setting);
	initialiser_boutonvolumeup(&volum_up);
	initialiser_boutonvolumedown(&volum_down);
	initialiser_boutonFullScreen(&fullscreen);
	initialiser_boutonRetour1(&retour1);
	initialiser_boutonMute(&mute);

	//Score
	
	//Credit
	
	//Leave
	musique=Mix_LoadMUS("son/Y2meta.app - Jesús Martín - Ryse Son Of Rome [ Epic Soundtrack Battle Music ] UEM (128 kbps).mp3");
	Mix_PlayMusic(musique,-1);
	song_bref=Mix_LoadWAV("son/mouseclick.wav");
/*****BOUCLE DU JEUX*****/
	while(boucle==1)
	{
		// LES ALLOCATION DYNAMIQUE SONT INTERDIT!!!!
		//IMG_Load
		//SDL_SetVideoMode
		//ttfRenderText...
		if(set==1)
		{
                     
			afficher_back(screen , back_setting) ;
			afficher_bouton(screen , volum_up);
			afficher_bouton(screen , volum_down);
			afficher_bouton(screen , fullscreen);
			afficher_bouton(screen , retour1);
			afficher_bouton(screen , mute);
		}
               else if(menu==1)
		    {
                         
 afficher_back(screen , back_menu) ;
}

		SDL_Flip(screen);
		/****LECTURE DES EVENNEMENT****/
		while(SDL_PollEvent(&event))
		{
		switch(event.type)
		{
			case SDL_QUIT:
				boucle = 0;
				break ;
			case SDL_MOUSEMOTION:
				if(set==1)
				{
					if(event.motion.x>volum_up.pos.x && event.motion.x<volum_up.pos.x+volum_up.pos.w
					&&event.motion.y>volum_up.pos.y && event.motion.y<volum_up.pos.y+volum_up.pos.h)	
					{
						volum_up.p=1;
						Mix_PlayChannel( -1,song_bref,0);
					}
					else if(event.motion.x>volum_down.pos.x && event.motion.x<volum_down.pos.x+volum_down.pos.w
					&&event.motion.y>volum_down.pos.y && event.motion.y<volum_down.pos.y+volum_down.pos.h)
					{
						volum_down.p=1;
						Mix_PlayChannel( -1,song_bref,0);
					}
					else if(event.motion.x>fullscreen.pos.x && event.motion.x<fullscreen.pos.x+fullscreen.pos.w
					&&event.motion.y>fullscreen.pos.y && event.motion.y<fullscreen.pos.y+fullscreen.pos.h)
					{
						fullscreen.p=1;
						Mix_PlayChannel( -1,song_bref,0);
					}
					else if(event.motion.x>retour1.pos.x && event.motion.x<retour1.pos.x+retour1.pos.w
					&&event.motion.y>retour1.pos.y && event.motion.y<retour1.pos.y+retour1.pos.h)
					{
						retour1.p=1;
						Mix_PlayChannel( -1,song_bref,0);
					}
					else if(event.motion.x>mute.pos.x && event.motion.x<mute.pos.x+mute.pos.w
					&&event.motion.y>mute.pos.y && event.motion.y<mute.pos.y+mute.pos.h)
					{
						mute.p=1;
						Mix_PlayChannel( -1,song_bref,0);
					}
					else 
					{
						volum_up.p=0;
						volum_down.p=0;
						fullscreen.p=0;
						retour1.p=0;
						mute.p=0;
					}
				}
				
				break;
			case SDL_MOUSEBUTTONUP:
				if(set==1)
				{
					if(event.motion.x>volum_up.pos.x && event.motion.x<volum_up.pos.x+volum_up.pos.w
					&&event.motion.y>volum_up.pos.y && event.motion.y<volum_up.pos.y+volum_up.pos.h)	
					{
						if(volum!=10)
						{
							volum++;			
							Mix_VolumeMusic((128*volum*10)/100);
						}
					}
					else if(event.motion.x>volum_down.pos.x && event.motion.x<volum_down.pos.x+volum_down.pos.w
					&&event.motion.y>volum_down.pos.y && event.motion.y<volum_down.pos.y+volum_down.pos.h)
					{
						if(volum!=0)
						{
							volum--;			
							Mix_VolumeMusic((128*volum*10)/100);
						}
					}
					else if(event.motion.x>fullscreen.pos.x && event.motion.x<fullscreen.pos.x+fullscreen.pos.w
					&&event.motion.y>fullscreen.pos.y && event.motion.y<fullscreen.pos.y+fullscreen.pos.h)
					{
						SDL_WM_ToggleFullScreen(screen);
					}
					else if(event.motion.x>retour1.pos.x && event.motion.x<retour1.pos.x+retour1.pos.w
					&&event.motion.y>retour1.pos.y && event.motion.y<retour1.pos.y+retour1.pos.h)
					{
						set=0;
						menu=1;
						
					}
					else if(event.motion.x>mute.pos.x && event.motion.x<mute.pos.x+mute.pos.w
					&&event.motion.y>mute.pos.y && event.motion.y<mute.pos.y+mute.pos.h)
					{
						if(volum!=0)
						{
							volum=0;
							mute.p=1;
							Mix_VolumeMusic((128*volum*10)/100);
						}
						else
						{
							volum=1;
							mute.p=0;
							Mix_VolumeMusic((128*volum*10)/100);
						}
					}
				}
				
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym==SDLK_f || event.key.keysym.sym==SDLK_n)
				{
					SDL_WM_ToggleFullScreen(screen);
				}
				if(set==1)
				{
					if(event.key.keysym.sym==SDLK_KP_PLUS)
					{
						if(volum!=10)
						{
							volum++;			
							Mix_VolumeMusic((128*volum*10)/100);
						}
					}
					else if(event.key.keysym.sym==SDLK_KP_MINUS)
					{
						if(volum!=0)
						{
							volum--;			
							Mix_VolumeMusic((128*volum*10)/100);
						}
					}
					else if(event.key.keysym.sym==SDLK_m)
					{
						if(volum!=0)
						{
							volum=0;
							mute.p=1;
							Mix_VolumeMusic((128*volum*10)/100);
						}
						else
						{
							volum=1;
							mute.p=0;
							Mix_VolumeMusic((128*volum*10)/100);
						}
					}
				}
				break;
		}
		}
		
		annimer_back(&back_menu);
		SDL_Delay(200);
	}
	
	liberer_back(&back_menu);
	liberer_texte(&txt_menu);
	Mix_FreeMusic (musique);
	Mix_FreeChunk(song_bref);
	TTF_Quit();
	
}
