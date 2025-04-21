#include "header.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>


void initBackg(background *b) {
    b->image = IMG_Load("back.png");
    if (b->image == NULL) {
        printf("Echec de chargement de l'image : %s\n", IMG_GetError());
        exit(1);
    }
    b->posimg.x = 0;
    b->posimg.y = 0;
    b->posimg.w = b->image->w;
    b->posimg.h = b->image->h;

    b->music = Mix_LoadMUS("palestine (copy).mp3");
    if (b->music == NULL) {
        printf("Echec de chargement de la musique : %s\n", Mix_GetError());
        exit(1);
    }
    Mix_PlayMusic(b->music, -1);
}

void afficherBack(background *b, SDL_Surface *ecran) {
    SDL_BlitSurface(b->image, NULL, ecran, &b->posimg);
}

void initialiseperso(perso *p) {
    p->sprite = IMG_Load("sprite123.png");
    if (p->sprite == NULL) {
        printf("Echec de chargement sprite : %s\n", IMG_GetError());
        exit(1);
    }

    p->sprite_health = IMG_Load("health.png");
    if (p->sprite_health == NULL) {
        printf("Echec de chargement health : %s\n", IMG_GetError());
        exit(1);
    }

    p->posSprite.x = 0;
    p->posSprite.y = 0;
    p->posSprite.w = p->sprite->w / 8;
    p->posSprite.h = p->sprite->h / 2;

    p->postScreen.x = 100;
    p->postScreen.y = 480;
    p->postScreen.w = p->posSprite.w;
    p->postScreen.h = p->posSprite.h;

    p->poshealth.x = 0;
    p->poshealth.y = 0;
    p->poshealth.w = p->sprite_health->w / 9;
    p->poshealth.h = p->sprite_health->h;

    p->poshealth2.x = 70; // Top-left corner with some padding
    p->poshealth2.y = 10; // Top-left corner with some padding
    p->poshealth2.w = p->poshealth.w; // Match the width of the health segment
    p->poshealth2.h = p->poshealth.h; // Match


    p->v = 0;
    p->acc = 0;
    p->vy = 0;
    p->en_air = 0;
    p->jump_count = 0;
    p->dir = 0;
    p->vie = 100;
    p->score = 0;
    p->precise_x = p->postScreen.x;

}

void animateperso(perso *p) {
    if (p->posSprite.x >= (p->sprite->w - p->posSprite.w)) {
        p->posSprite.x = 0;
    } else {
        p->posSprite.x += p->posSprite.w;
    }
    p->posSprite.y = p->dir * p->posSprite.h;
}

void blitperso(perso *p, SDL_Surface *screen) {
    SDL_BlitSurface(p->sprite, &p->posSprite, screen, &p->postScreen);
}

void moveperso(perso *p, Uint32 dt) {
    double t = dt / 1000.0;

    p->v += p->acc * t;
    if (p->v < 0) p->v = 0;
    if (p->v > 5) p->v = 5;

    if (p->dir == 0) {
        p->precise_x += p->v * t * 100;
    } else if (p->dir == 1) {
        p->precise_x -= p->v * t * 100;
    }

    // Update real screen position
    p->postScreen.x = (int)p->precise_x;
}


void saut(perso *p, int dt) {
    double t = dt / 1000.0;

    if (p->en_air) {
        p->vy += 9.8 * t;
        p->postScreen.y += (int)(p->vy * t * 100);

        if (p->postScreen.y >= 480) {
            p->postScreen.y = 480;
            p->vy = 0;
            p->en_air = 0;
            p->jump_count = 0;
        }
    }
}
void health(perso *p)
{
    // Exact pixel positions based on sprite width (1826px / 9 frames)
    int positions[9] = {
        0,      // Frame 0: 100–91
        204,    // Frame 1: 90–71
        415,    // Frame 2: 70–61
        618,    // Frame 3: 60–51
        818,    // Frame 4: 50–41
        1020,   // Frame 5: 40–31
        1222,   // Frame 6: 30–21
        1421,   // Frame 7: 20–11
        1624    // Frame 8: 10–1
    };

    if (p->vie <= 100 && p->vie > 90) {
        p->poshealth.x = positions[0];
    } else if (p->vie <= 90 && p->vie > 70) {
        p->poshealth.x = positions[1];
    } else if (p->vie <= 70 && p->vie > 60) {
        p->poshealth.x = positions[2];
    } else if (p->vie <= 60 && p->vie > 50) {
        p->poshealth.x = positions[3];
    } else if (p->vie <= 50 && p->vie > 40) {
        p->poshealth.x = positions[4];
    } else if (p->vie <= 40 && p->vie > 30) {
        p->poshealth.x = positions[5];
    } else if (p->vie <= 30 && p->vie > 20) {
        p->poshealth.x = positions[6];
    } else if (p->vie <= 20 && p->vie > 10) {
        p->poshealth.x = positions[7];
    } else if (p->vie <= 10 && p->vie > 0) {
        p->poshealth.x = positions[8];
    }

    // Set width and height of the frame explicitly
    p->poshealth.w = 205;                // Closest rounded width
    p->poshealth.y = 0;
    p->poshealth.h = p->sprite_health->h;
}
void afficherhealth(perso *p, SDL_Surface *screen)
{
    SDL_BlitSurface(p->sprite_health, &p->poshealth, screen, &p->poshealth2);
}
void initMoney(money *m) {
    m->sprite = IMG_Load("money.png"); 
    if (m->sprite == NULL) {
        printf("Erreur chargement money : %s\n", IMG_GetError());
        exit(1);
    }
    m->coinSound = Mix_LoadWAV("coin.wav"); // <- your sound file here
    if (m->coinSound == NULL) {
        printf("Erreur chargement son coin : %s\n", Mix_GetError());
        exit(1);
    }

    m->pos.x = 300; // set where you want it
    m->pos.y = 480;
    m->pos.w = m->sprite->w;
    m->pos.h = m->sprite->h;
    m->collected = 0;
}
void afficherMoney(money *m, SDL_Surface *screen) {
    if (!m->collected) {
        SDL_BlitSurface(m->sprite, NULL, screen, &m->pos);
    }
}
void afficherScore(SDL_Surface *screen, TTF_Font *font, int score, SDL_Color color) {
    char buffer[50];
    sprintf(buffer, " %d", score);
    SDL_Surface *text = TTF_RenderText_Blended(font, buffer, color);
    SDL_Rect pos = {600, 20};
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);
}
int checkCollision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w < b.x) return 0; // a is left of b
    if (a.x > b.x + b.w) return 0; // a is right of b
    if (a.y + a.h < b.y) return 0; // a is above b
    if (a.y > b.y + b.h) return 0; // a is below b
    return 1; // rectangles overlap = collision
}
void initEnemy(enemy *e) {
    e->box.x = 500;
    e->box.y = 500;
    e->box.w = 50;
    e->box.h = 50;
    e->touched = 0;
    e->direction = 1;  // start moving left
    e->speed = 2;      // pixels per frame
}

void drawEnemy(enemy *e, SDL_Surface *screen) {
    Uint32 red = SDL_MapRGB(screen->format, 255, 0, 0);
    SDL_FillRect(screen, &e->box, red);
}

void moveEnemy(enemy *e) {
    if (e->direction == 0) {
        e->box.x += e->speed;
        if (e->box.x + e->box.w >= 800) { // right edge
            e->direction = 1;
        }
    } else {
        e->box.x -= e->speed;
        if (e->box.x <= 0) { // left edge
            e->direction = 0;
        }
    }
}
void initHeart(heart_pickup *h) {
    h->sprite = IMG_Load("heart .png");
    if (!h->sprite) {
        printf("Erreur chargement heart pickup: %s\n", IMG_GetError());
        exit(1);
    }
    h->pickupSound = Mix_LoadWAV("pickup.wav"); // your sound file
    if (!h->pickupSound) {
        printf("Erreur son heart pickup: %s\n", Mix_GetError());
        exit(1);
    }
    h->pos.x = 600;
    h->pos.y = 500;
    h->pos.w = h->sprite->w;
    h->pos.h = h->sprite->h;
    h->collected = 0;
}

void afficherHeart(heart_pickup *h, SDL_Surface *screen, Uint32 startTime) {
    if (!h->collected && SDL_GetTicks() - startTime > 5000) {
        SDL_BlitSurface(h->sprite, NULL, screen, &h->pos);
    }
}


