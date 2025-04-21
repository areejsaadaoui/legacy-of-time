#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "header.h"

#define COIN_COUNT 5

int main(int argc, char *argv[]) {
    int quitter = 1;
    background *b = malloc(sizeof(background));
    perso *p = malloc(sizeof(perso));
    SDL_Surface *ecran, *heart, *star, *score;
    SDL_Rect pos_heart, pos_star, pos_score;
    heart_pickup h;

    SDL_Event event;
    enemy e;

    Uint32 dt = 0, t_prev = SDL_GetTicks();
    Uint32 startTime = SDL_GetTicks();


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("Erreur SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    SDL_Color black = {0, 0, 0};
    if (!font) {
        printf("Erreur police: %s\n", TTF_GetError());
        return 1;
    }

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        printf("Erreur fenêtre: %s\n", SDL_GetError());
        return 1;
    }

    heart = IMG_Load("heart .png");
    star = IMG_Load("star.png");
    score = IMG_Load("score.png");
    if (!heart || !star || !score) {
        printf("Erreur chargement UI: %s\n", IMG_GetError());
        return 1;
    }

    pos_heart = (SDL_Rect){10, 10, heart->w, heart->h};
    pos_star = (SDL_Rect){730, 10, star->w, star->h};
    pos_score = (SDL_Rect){500, 10, score->w, score->h};

    money coins[COIN_COUNT];
    for (int i = 0; i < COIN_COUNT; i++) {
        initMoney(&coins[i]);
        coins[i].pos.x = 200 + i * 100;
        coins[i].pos.y = 500;
    }

    int right_pressed = 0, left_pressed = 0;

    initBackg(b);
    initialiseperso(p);
    initHeart(&h);

    initEnemy(&e);

    while (quitter) {
        Uint32 t_now = SDL_GetTicks();
        dt = t_now - t_prev;
        t_prev = t_now;

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quitter = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quitter = 0;
                            break;
                        case SDLK_RIGHT:
                            right_pressed = 1;
                            p->dir = 0;
                            break;
                        case SDLK_LEFT:
                            left_pressed = 1;
                            p->dir = 1;
                            break;
                        case SDLK_SPACE:
                            if (p->jump_count < 2) {
                                p->vy = -6;
                                p->en_air = 1;
                                p->jump_count++;
                            }
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT:
                            right_pressed = 0;
                            break;
                        case SDLK_LEFT:
                            left_pressed = 0;
                            break;
                    }
                    break;
            }
        }

        if (right_pressed) {
            if (p->acc < 0.01) p->acc = 0.01;
            p->acc += 0.01;
            moveperso(p, dt);
            animateperso(p);
        } else if (left_pressed) {
            if (p->acc > -0.01) p->acc = -0.01;
            p->acc -= 0.01;
            moveperso(p, dt);
            animateperso(p);
        } else {
            if (p->acc > 0) p->acc -= 0.003;
            if (p->acc < 0) p->acc += 0.003;
        }

        saut(p, dt);
        moveEnemy(&e);
        
        if (e.box.x < 0 || e.box.x > 800) {
            e.box.x = 300; // reset to visible position
            e.direction = 1;
        }
        


        // Coins logic
        for (int i = 0; i < COIN_COUNT; i++) {
            if (!coins[i].collected && checkCollision(p->postScreen, coins[i].pos)) {
                coins[i].collected = 1;
                p->score += 10;
                Mix_PlayChannel(-1, coins[i].coinSound, 0);
            }
        }
        // Heart logic
        if (!h.collected && SDL_GetTicks() - startTime > 5000 && checkCollision(p->postScreen, h.pos)) {

            h.collected = 1;
            p->vie += 20;
            Mix_PlayChannel(-1, h.pickupSound, 0);

            if (p->vie > 100) p->vie = 100;
            printf("Picked up heart! Vie: %d\n", p->vie);
        }
        

        // Enemy logic
        int enemy_collision = checkCollision(p->postScreen, e.box);
        const Uint8 *keys = SDL_GetKeyState(NULL);

        if (enemy_collision) {
            if (keys[SDLK_l]) {
                if (!e.touched) {
                    p->score += 20;
                    printf("Enemy hit! Score: %d\n", p->score);
                    e.touched = 1;
                }
            } else {
                if (!e.touched) {
                    p->vie -= 10;
                    printf("Ouch! Vie: %d\n", p->vie);
                    if (p->dir == 0) {
                        p->precise_x -= 30;
                    } else {
                        p->precise_x += 30;
                    }
                    p->postScreen.x = (int)p->precise_x;
                    e.touched = 1;
                }
            }
        } else {
            e.touched = 0;
        }
        if (p->vie <= 0) {
            printf("Game Over! Final Score: %d\n", p->score);
            quitter = 0;
        }

        // RENDERING
        afficherBack(b, ecran);
        drawEnemy(&e, ecran);
        blitperso(p, ecran);
        afficherHeart(&h, ecran, startTime);

        health(p);
        afficherhealth(p, ecran);
        SDL_BlitSurface(heart, NULL, ecran, &pos_heart);
        SDL_BlitSurface(star, NULL, ecran, &pos_star);
        SDL_BlitSurface(score, NULL, ecran, &pos_score);

        for (int i = 0; i < COIN_COUNT; i++) {
            afficherMoney(&coins[i], ecran);
        }

        afficherScore(ecran, font, p->score, black);
        SDL_Flip(ecran);
    }

    // CLEANUP
    SDL_FreeSurface(b->image);
    Mix_FreeMusic(b->music);
    SDL_FreeSurface(p->sprite);
    SDL_FreeSurface(p->sprite_health);
    for (int i = 0; i < COIN_COUNT; i++) {
        SDL_FreeSurface(coins[i].sprite);
        Mix_FreeChunk(coins[i].coinSound);
    }
    Mix_FreeChunk(h.pickupSound);
    SDL_FreeSurface(h.sprite);

    SDL_FreeSurface(heart);
    SDL_FreeSurface(star);
    SDL_FreeSurface(score);
    free(b);
    free(p);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
