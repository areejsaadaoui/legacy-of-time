#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "boutons.h"
#include "background.h"
int main(int argc, char *argv[]) {
 int quitter = 1;
    int x, y, i, j;
    int bou_j=-1,jou=-1,input=-1;
    background *b = malloc(sizeof(background));
    boutton *boutons[8];
    SDL_Surface *ecran;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur d'initialisation de SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }
     
     ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        return 1;
    }
    initBackg(b);
    for (i = 0; i < 6; i++) {
        boutons[i] = malloc(sizeof(boutton));
        if (boutons[i] == NULL) {
            printf("Memory allocation failed for button %d.\n", i);
            return 1;
        }
    }
    initboutton(boutons);
    while (quitter) {
            afficherBack(b, ecran);
        afficherboutton(boutons, ecran, b->niveau);
        
        while (SDL_PollEvent(&event)){
           switch (event.type){
               case SDL_QUIT:
                    quitter = 0;
                break;
            case SDL_KEYDOWN:
                 switch (event.key.keysym.sym){
                 case SDLK_ESCAPE:
                            if (b->niveau == 0)
                                quitter = 0;
                            else
                                b->niveau = 0;
                break;
                case SDLK_p:
                    b->niveau = 1;
                break;

                
}
    case SDL_MOUSEMOTION:
         x = event.motion.x;
         y = event.motion.y;
         switch(b->niveau){
         case 0:
             if ((x >= boutons[0]->posimg.x) && (x <= boutons[0]->posimg.x + boutons[0]->posimg.w) &&(y >= boutons[0]->posimg.y) && (y <= boutons[0]->posimg.y + boutons[0]->posimg.h) ){
              boutons[0]->actif = 1;
                                  Mix_PlayChannel(-1, boutons[0]->son, 0);
                                  boutons[1]->actif = 0;
                                  boutons[2]->actif = 0;
  
             }
             else if ((x >= boutons[1]->posimg.x) && (x <= boutons[1]->posimg.x + boutons[1]->posimg.w) &&(y >= boutons[1]->posimg.y) && (y <= boutons[1]->posimg.y + boutons[1]->posimg.h)){
                                  boutons[1]->actif = 1;
                                  Mix_PlayChannel(-1, boutons[1]->son, 0);
                                  boutons[0]->actif = 0;
                                  boutons[2]->actif = 0;
   
             }
             else if ((x >= boutons[2]->posimg.x) && (x <= boutons[2]->posimg.x + boutons[2]->posimg.w) &&(y >= boutons[2]->posimg.y) && (y <= boutons[2]->posimg.y + boutons[2]->posimg.h)){
                               boutons[2]->actif = 1;
                               Mix_PlayChannel(-1, boutons[2]->son, 0);
                               boutons[0]->actif = 0;
                               boutons[1]->actif = 0;
  
             }
             else{
               for (j = 0; j < 3; j++)
                            boutons[j]->actif = 0;
 
             }
             
             
             break;
         case 1:
            if ((x >= boutons[2]->posimg.x) && (x <= boutons[2]->posimg.x + boutons[2]->posimg.w) &&(y >= boutons[2]->posimg.y) && (y <= boutons[2]->posimg.y + boutons[2]->posimg.h) ){
                                  boutons[2]->actif = 1;
                                  Mix_PlayChannel(-1, boutons[2]->son, 0);
                                  boutons[3]->actif = 0;  
            }
            else if ((x >= boutons[3]->posimg.x) && (x <= boutons[3]->posimg.x + boutons[3]->posimg.w) &&(y >= boutons[3]->posimg.y) && (y <= boutons[3]->posimg.y + boutons[3]->posimg.h)){
                               boutons[3]->actif = 1;
                               Mix_PlayChannel(-1, boutons[3]->son, 0);
                               boutons[2]->actif = 0;   
            }
            else if ((x >= boutons[4]->posimg.x) && (x <= boutons[4]->posimg.x + boutons[4]->posimg.w) &&
                               (y >= boutons[4]->posimg.y) && (y <= boutons[4]->posimg.y + boutons[4]->posimg.h)){
                               boutons[4]->actif = 1;
                                  Mix_PlayChannel(-1, boutons[4]->son, 0);
                                  boutons[2]->actif = 0;
                                  boutons[3]->actif = 0;
                                  boutons[5]->actif = 0;}
           else if ((x >= boutons[5]->posimg.x) && (x <= boutons[5]->posimg.x + boutons[5]->posimg.w) &&
                               (y >= boutons[5]->posimg.y) && (y <= boutons[5]->posimg.y + boutons[5]->posimg.h)){
                               boutons[5]->actif = 1;
                                  Mix_PlayChannel(-1, boutons[5]->son, 0);
                                  boutons[2]->actif = 0;
                                  boutons[3]->actif = 0;
}
           else if ((x >= boutons[6]->posimg.x) && (x <= boutons[6]->posimg.x + boutons[6]->posimg.w) &&(y >= boutons[6]->posimg.y) && (y <= boutons[6]->posimg.y + boutons[6]->posimg.h)){
            boutons[6]->actif = 1;
                                  Mix_PlayChannel(-1, boutons[6]->son, 0);
                                  boutons[2]->actif = 0;
                                  boutons[3]->actif = 0;
           }
           else if ((x >= boutons[7]->posimg.x) && (x <= boutons[7]->posimg.x + boutons[7]->posimg.w) &&
                               (y >= boutons[7]->posimg.y) && (y <= boutons[7]->posimg.y + boutons[7]->posimg.h)){
                                  boutons[7]->actif = 1;
                                  Mix_PlayChannel(-1, boutons[6]->son, 0);
                                  boutons[2]->actif = 0;
                                  boutons[3]->actif = 0;                    
                               }
          else{
           boutons[2]->actif = 0;
           boutons[3]->actif = 0;
          if(bou_j==0){
           if(jou!=1)
                boutons[4]->actif=0;
           if(jou!=2)
                boutons[5]->actif=0;
           if(input!=1)
                boutons[6]->actif=0;
           if(input!=2)
                boutons[7]->actif=0;}
                


           


             
          }
          
            
            break;
             }

        
        break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT){
              x = event.button.x;
              y = event.button.y;
              switch(b->niveau)
              {
                case 0:
                   if (x >= boutons[0]->posimg.x && x <= boutons[0]->posimg.x + boutons[0]->posimg.w &&y >= boutons[0]->posimg.y && y <= boutons[0]->posimg.y + boutons[0]->posimg.h ) 
                   {
                      b->niveau=1;
                      bou_j=0; 
                   }
                   else if (x >= boutons[1]->posimg.x && x <= boutons[1]->posimg.x + boutons[1]->posimg.w &&y >= boutons[1]->posimg.y && y <= boutons[1]->posimg.y + boutons[1]->posimg.h)
                   {
                        b->niveau = 1;
                        bou_j=1;
                   }
                    else if (x >= boutons[2]->posimg.x && x <= boutons[2]->posimg.x + boutons[2]->posimg.w &&y >= boutons[2]->posimg.y && y <= boutons[2]->posimg.y + boutons[2]->posimg.h )
                        b->niveau=0;
                    

                   
                    break;
                    case 1:
                      if (x >= boutons[2]->posimg.x && x <= boutons[2]->posimg.x + boutons[2]->posimg.w &&y >= boutons[2]->posimg.y && y <= boutons[2]->posimg.y + boutons[2]->posimg.h )
                            b->niveau=0;
                    if(bou_j==0)
                    {
                       if (x >= boutons[4]->posimg.x && x <= boutons[4]->posimg.x + boutons[4]->posimg.w &&
                                 y >= boutons[4]->posimg.y && y <= boutons[4]->posimg.y + boutons[4]->posimg.h )
                                 {
                                 jou=1;
                                 boutons[4]->actif = 1;
                                 boutons[5]->actif = 0; 
                                 }
                     else if (x >= boutons[5]->posimg.x && x <= boutons[5]->posimg.x + boutons[5]->posimg.w &&
                                 y >= boutons[5]->posimg.y && y <= boutons[5]->posimg.y + boutons[5]->posimg.h )
                                 {
                                jou=2;
                                 boutons[4]->actif = 0;
                                 boutons[5]->actif = 1; 
                                 }
                    else if (x >= boutons[6]->posimg.x && x <= boutons[6]->posimg.x + boutons[6]->posimg.w &&
                                 y >= boutons[6]->posimg.y && y <= boutons[6]->posimg.y + boutons[6]->posimg.h )
                                 {
                                 input=1;
                                 boutons[7]->actif = 0;
                                 boutons[6]->actif = 1; 
                                 }
                   else if (x >= boutons[7]->posimg.x && x <= boutons[7]->posimg.x + boutons[7]->posimg.w &&
                                 y >= boutons[7]->posimg.y && y <= boutons[7]->posimg.y + boutons[7]->posimg.h )
                                 {
                                   input=2;
                                 boutons[7]->actif = 1;
                                 boutons[6]->actif = 0;  
                                 }
                  else if (x >= boutons[3]->posimg.x && x <= boutons[3]->posimg.x + boutons[3]->posimg.w &&
                                 y >= boutons[3]->posimg.y && y <= boutons[3]->posimg.y + boutons[3]->posimg.h )
                                 {
                                     if((jou!=-1)&&(input!=-1))
                                        b->niveau=0;
                                        
                                 }
                    
                      
                      
                    }
                    if(bou_j==1){
                            if (x >= boutons[4]->posimg.x && x <= boutons[4]->posimg.x + boutons[4]->posimg.w && y >= boutons[4]->posimg.y && y <= boutons[4]->posimg.y + boutons[4]->posimg.h )
                               boutons[4]->actif = 1;
                            else if (x >= boutons[5]->posimg.x && x <= boutons[5]->posimg.x + boutons[5]->posimg.w && y >= boutons[5]->posimg.y && y <= boutons[5]->posimg.y + boutons[5]->posimg.h )
                               boutons[5]->actif = 1;
                            else if (x >= boutons[6]->posimg.x && x <= boutons[6]->posimg.x + boutons[6]->posimg.w && y >= boutons[6]->posimg.y && y <= boutons[6]->posimg.y + boutons[6]->posimg.h )
                               boutons[6]->actif = 1;
                            else if (x >= boutons[7]->posimg.x && x <= boutons[7]->posimg.x + boutons[7]->posimg.w && y >= boutons[7]->posimg.y && y <= boutons[7]->posimg.y + boutons[7]->posimg.h )
                               boutons[7]->actif = 1;
                            else if (x >= boutons[3]->posimg.x && x <= boutons[3]->posimg.x + boutons[3]->posimg.w && y >= boutons[3]->posimg.y && y <= boutons[3]->posimg.y + boutons[5]->posimg.h )
                                {
                                    if((boutons[4]->actif == 1)&&(boutons[5]->actif == 1)&&(boutons[6]->actif == 1)&&(boutons[7]->actif == 1))
                                       b->niveau=0;
                                        
                                }
                            
                                
                            
                            

                        
                    }
                    
                      
                        break;  
              }
   
            }
            
            break;
        
                
        
           } 
        }
      SDL_Flip(ecran);
        
    }










cleanBack(b);
    cleanboutton(boutons);
    free(b);
    SDL_Quit();

return 0;
}
