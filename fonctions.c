#include "background.h"
#include "boutons.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h> 
#include <stdlib.h>  

void initBackg(background *b) {
    int i;
    char *nom[] = {"backgroun0.png", "background1.png", "aaa.png"};

    for (i = 0; i < 3; i++) {
        b->image[i] = IMG_Load(nom[i]);
        if (b->image[i] == NULL) {
            printf("Echec de chargement de l'image : %s\n", IMG_GetError());
            exit(1);
        }
    }

    b->posimg.x = 0;
    b->posimg.y = 0;
    b->posimg.w = b->image[0]->w;  
    b->posimg.h = b->image[0]->h;

    b->music = Mix_LoadMUS("palestine (copy).mp3");
    Mix_PlayMusic(b->music, -1);
    if (b->music == NULL) {
        printf("Echec de chargement de la musique : %s\n", Mix_GetError());
        exit(1);
    }
    b->niveau = 0;
}

void afficherBack(background *b, SDL_Surface *ecran) {
    SDL_BlitSurface(b->image[b->niveau], NULL, ecran, &b->posimg);
}

void cleanBack(background *b) {
    int i;
    Mix_FreeMusic(b->music);
    Mix_CloseAudio();

    for (i = 0; i < 3; i++) {
        SDL_FreeSurface(b->image[i]);
    }

    SDL_Quit();
}
void initboutton(boutton *b[]) {
    int i;
    char *nom[] = {"monojou0.png", "monojou1.png", "multijou0.png", "multijou1.png", "retour0.png", "retour1.png", "valider0.png", "valider1.png","roam.png","roam1.png","roana0.png","roana1.png","input 1off.png","input1on.png","input2off.png","input2on.png"};
    
    for (i = 0; i < 8; i++) {
        b[i] = malloc(sizeof(boutton));
        if (b[i] == NULL) {
            printf("Echec d'allocation mémoire pour le bouton %d.\n", i);
            exit(1);
        }

        b[i]->image[0] = IMG_Load(nom[2 * i]);     
        b[i]->image[1] = IMG_Load(nom[2 * i + 1]); 

        if (b[i]->image[0] == NULL || b[i]->image[1] == NULL) {
            printf("Echec de chargement de l'image pour le bouton %d.\n", i);
            exit(1);
        }

        // Assign position for each button
        switch(i) {
            case 0:
                b[i]->posimg.x = 400 - b[i]->image[0]->w / 2;
                b[i]->posimg.y = 200; 
                break;
            case 1:
                b[i]->posimg.x = 400 - b[i]->image[0]->w / 2;
                b[i]->posimg.y = 400;
                break;
            case 2:
                b[i]->posimg.x = 20;  
                b[i]->posimg.y = 600 - b[i]->image[0]->h - 20; 
                break;
            case 3:
                b[i]->posimg.x = 800 - b[i]->image[0]->w - 20; 
                b[i]->posimg.y = 600 - b[i]->image[0]->h - 20;
                break;
 
            case 4:
                b[i]->posimg.x = 230;
                b[i]->posimg.y = 120;
                break;
            case 5:
                 b[i]->posimg.x = 500;
                b[i]->posimg.y = 120;
                
                break;
           case 6:
               b[i]->posimg.x = 440;
                b[i]->posimg.y =400;
              break;
           case 7:
               b[i]->posimg.x = 190;
                b[i]->posimg.y =400;
              break;
            
        }
        
        b[i]->posimg.w = b[i]->image[0]->w;
        b[i]->posimg.h = b[i]->image[0]->h;
        b[i]->actif = 0; 

        // Load sound
        b[i]->son = Mix_LoadWAV("mouseclick.wav");
        if (b[i]->son == NULL) {
            printf("Echec de chargement du son : %s.\n", Mix_GetError());
            exit(1);
        }
    }
}

void afficherboutton(boutton *b[], SDL_Surface *ecran, int niv) {
    int i;
    if(niv == 0) {
        for (i = 0; i < 3; i++) {
            SDL_BlitSurface(b[i]->image[b[i]->actif], NULL, ecran, &b[i]->posimg);
        }
    }
    if(niv == 1) {
        for (i = 2; i < 8; i++) {
            SDL_BlitSurface(b[i]->image[b[i]->actif], NULL, ecran, &b[i]->posimg);
        }
    }
   
}

void cleanboutton(boutton *b[]) {
    int i;
    for (i = 0; i < 8; i++) {
        SDL_FreeSurface(b[i]->image[0]);
        SDL_FreeSurface(b[i]->image[1]);
        Mix_FreeChunk(b[i]->son);
        free(b[i]);
    }
}


