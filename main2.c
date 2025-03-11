#include "botton.h"
#include "background.h"
#include <stdio.h>
#include <stdlib.h> // Ajout pour malloc et free
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

int main(int argc, char** argv) {

if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //API Mixer Initialization
	{
	printf("%s", Mix_GetError());
	}
    TTF_Init();
    background b;

    SDL_Event event;
    Mix_Chunk* son;
    initBackg(&b);
    int loop=1,h=1;
    SDL_Surface *screen,*text;
    TTF_Font * font = TTF_OpenFont("neon.ttf", 40);
    SDL_Color color = {60,60,60};
    SDL_Rect postexte={380,300,0,0};
    boutton bout,boutres,boutquit;
    char ch[1000];
    son= Mix_LoadWAV("goodresult-82807.wav");
    if (!son) {
        printf("Erreur de chargement du son: %s\n", Mix_GetError());
        return 1;
    }
    initboutton(&bout,"ok.off.png","ok.on.png",380,390);
    initboutton(&boutres,"restart.off.png","restart.on.png",770,500);
    initboutton(&boutquit,"quit.off.png","quit.on.png",30,500);
    strcpy(ch,"");
    screen = SDL_SetVideoMode(959, 601, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    while(loop)
    {
        afficherBack(&b,screen);
        switch(b.niveau){
        case 0:
        text = TTF_RenderText_Blended(font, ch, color);
        SDL_BlitSurface(text,NULL,screen,&postexte);
        afficherboutton(&bout,screen);
        SDL_Flip(screen);
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop=0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_a:
                    strcat(ch, "a"); break;
                    case SDLK_b:
                    strcat(ch, "b"); break;
                    case SDLK_c:
                    strcat(ch, "c"); break;
                    case SDLK_d:
                    strcat(ch, "d"); break;
                    case SDLK_e:
                    strcat(ch, "e"); break;
                    case SDLK_f:
                    strcat(ch, "f"); break;
                    case SDLK_g:
                    strcat(ch, "g"); break;
                    case SDLK_h:
                    strcat(ch, "h"); break;
                    case SDLK_i:
                    strcat(ch, "i"); break;
                    case SDLK_j:
                    strcat(ch, "j"); break;
                    case SDLK_k:
                    strcat(ch, "k"); break;
                    case SDLK_l:
                    strcat(ch, "l"); break;
                    case SDLK_m:
                    strcat(ch, "m"); break;
                    case SDLK_n:
                    strcat(ch, "n"); break;
                    case SDLK_o:
                    strcat(ch, "o"); break;
                    case SDLK_p:
                    strcat(ch, "p"); break;
                    case SDLK_q:
                    strcat(ch, "q"); break;
                    case SDLK_r:
                    strcat(ch, "r"); break;
                    case SDLK_s:
                    strcat(ch, "s");break;
                    case SDLK_t:
                    strcat(ch, "t"); break;
                    case SDLK_u:
                    strcat(ch, "u"); break;
                    case SDLK_v:
                    strcat(ch, "v"); break;
                    case SDLK_w:
                    strcat(ch, "w"); break;
                    case SDLK_y:
                    strcat(ch, "y"); break;
                    case SDLK_z:
                    strcat(ch, "z"); break;
                    case SDLK_DELETE:
                    ch[strlen(ch)-1]='\0';break;
                    case SDLK_RETURN: b.niveau=1;break;}
                break;  
                case SDL_MOUSEMOTION:
                    if(event.motion.x>=bout.posimg.x && event.motion.x<bout.posimg.x+bout.posimg.w && event.motion.y>=bout.posimg.y && event.motion.y<bout.posimg.y+bout.posimg.h ){bout.actif=1;  Mix_PlayChannel(-1,son,0);} 
                    else bout.actif=0;

                    break; 
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.x>=bout.posimg.x && event.button.x<bout.posimg.x+bout.posimg.w && event.button.y>=bout.posimg.y && event.button.y<bout.posimg.y+bout.posimg.h )b.niveau=1;
                     break;     
                
                
                
                
                }




    }break;
    case 1:
        if(h){Mix_PlayChannel(-1,son,0);h=0;}
        afficherboutton(&boutres,screen);
        afficherboutton(&boutquit,screen);

        SDL_Flip(screen);
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop=0;
                break;
                
            case SDL_MOUSEMOTION:
                if(event.motion.x>=boutres.posimg.x && event.motion.x<boutres.posimg.x+boutres.posimg.w && event.motion.y>=boutres.posimg.y && event.motion.y<boutres.posimg.y+boutres.posimg.h ){boutres.actif=1; Mix_PlayChannel(-1,son,0);}
                else boutres.actif=0;
                if(event.motion.x>=boutquit.posimg.x && event.motion.x<boutquit.posimg.x+boutquit.posimg.w && event.motion.y>=boutquit.posimg.y && event.motion.y<boutquit.posimg.y+boutquit.posimg.h ){boutquit.actif=1; Mix_PlayChannel(-1,son,0);}
                else boutquit.actif=0;
                break;    
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x>=boutres.posimg.x && event.button.x<boutres.posimg.x+boutres.posimg.w && event.button.y>=boutres.posimg.y && event.button.y<boutres.posimg.y+boutres.posimg.h )b.niveau=0;
                if(event.button.x>=boutquit.posimg.x && event.button.x<boutquit.posimg.x+boutquit.posimg.w && event.button.y>=boutquit.posimg.y && event.button.y<boutquit.posimg.y+boutquit.posimg.h )loop=0;
                break;    
                
            case SDL_KEYDOWN:
                if(event.key.keysym.sym==SDLK_ESCAPE)loop=0;
                break;
                }
                }

        break;
    
    }


}
 cleanBack ( &b);
//free(b);



 }  
