#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    SDL_Surface *image;
    Mix_Music *music;
    SDL_Rect posimg;
} background;
typedef struct {
    SDL_Surface *sprite;
    SDL_Rect pos;
    Mix_Chunk *coinSound;
    int collected;
} money;
typedef struct {
    SDL_Surface *sprite;
    SDL_Rect pos;
    int collected;
    Mix_Chunk *pickupSound;

} heart_pickup;


typedef struct {
    SDL_Surface *sprite;
    SDL_Surface *sprite_health;
    SDL_Rect postScreen, posSprite, poshealth, poshealth2;
    int dir, vie, score;
    double v, acc;
    double vy;
    int en_air;
    int jump_count;
    double precise_x;

} perso;
typedef struct {
    SDL_Rect box;
    int touched;
    int direction; // 0 = right, 1 = left
    int speed;     // pixels per frame
} enemy;


void initEnemy(enemy *e);
void drawEnemy(enemy *e, SDL_Surface *screen);
void moveEnemy(enemy *e);


void initBackg(background *b);
void afficherBack(background *b, SDL_Surface *ecran);

void initialiseperso(perso *p);
void animateperso(perso *p);
void blitperso(perso *p, SDL_Surface *screen);
void moveperso(perso *p, Uint32 dt);
void saut(perso *p, int dt);

void initMoney(money *m);
void afficherMoney(money *m, SDL_Surface *screen);
void afficherScore(SDL_Surface *screen, TTF_Font *font, int score, SDL_Color color);


void health(perso *p);
void afficherhealth(perso *p, SDL_Surface *screen);
int checkCollision(SDL_Rect a, SDL_Rect b);

void initHeart(heart_pickup *h);
void afficherHeart(heart_pickup *h, SDL_Surface *screen, Uint32 startTime);



#endif

