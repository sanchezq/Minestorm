#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "enemy.h"

#define BACKGROUNDSHEET_PATH "assets/background.png"
#define SPRITESHEET_PATH "assets/spritesheet.png"
#define BORDERSHEET_PATH "assets/border.png"
#define PAUSESHEET_PATH "assets/pause.png"
#define MENUSHEET_PATH "assets/menu.png"
#define LIFESHEET_PATH "assets/life.png"

#define BACKGROUND_W 160
#define BACKGROUND_H 225

#define SPRITE_MENU_W 640
#define SPRITE_MENU_H 900

#define SPRITE_PAUSE_W 640
#define SPRITE_PAUSE_H 900

#define SPRITE_LIFE_W 640
#define SPRITE_LIFE_H 900

#define SPRITE_LIFE_LOOSE_X 296
#define SPRITE_LIFE_LOOSE_Y 152
#define SPRITE_LIFE_LOOSE_W 16

#define LIFE_LOOSE_X1 133
#define LIFE_LOOSE_X2 168
#define LIFE_LOOSE_Y 116
#define LIFE_LOOSE_W 16

#define PAUSE_W 128
#define PAUSE_H 176

#define SPRITE_PLAYER_XPOS 50
#define SPRITE_PLAYER_YPOS 272
#define SPRITE_PLAYER_W 22
#define SPRITE_PLAYER_H 12

#define SPRITE_SHOT_ENEMY_XPOS 304
#define SPRITE_SHOT_PLAYER_XPOS 288
#define SPRITE_SHOT_YPOS 136
#define SPRITE_SHOT_W 8

#define	SPRITE_MINES_YPOS 42

#define	SPRITE_FLOATING_XPOS 10
#define	SPRITE_FLOATING_FIRE_XPOS 34
#define	SPRITE_FLOATING_W 12

#define	SPRITE_MAGNETIC_XPOS 58
#define	SPRITE_MAGNETIC_FIRE_XPOS 81
#define	SPRITE_MAGNETIC_FIRE_YPOS 41
#define	SPRITE_MAGNETIC_W 12
#define	SPRITE_MAGNETIC_FIRE_W 14

#define	SPRITE_SPAWNPOINT_XPOS 154
#define	SPRITE_SPAWNPOINT_YPOS 138
#define	SPRITE_SPAWNPOINT_W 12

#define SPAWNPOINT_SIZE 10

char str_score[20];

void place_sprite(SDL_Window* window, SDL_Surface* surface, SDL_Rect spriteLoc, SDL_Rect rect);

void place_background(SDL_Window * window);
void place_border(SDL_Window * window);
void place_menu(SDL_Window * window);

void renderer_show(SDL_Window * window);
void renderer_clear(SDL_Window * window);

void place_floating(SDL_Window * window);
void place_magnetic(SDL_Window * window);

void show_hitbox(SDL_Window * window, SDL_Rect rect);
void show_hitbox_player(SDL_Window* window);

void print_pause(SDL_Window * window);
void print_life(SDL_Window * window);
void place_life_loose(SDL_Window * window);

void place_spawnpoint_floating(SDL_Window * window);
void place_spawnpoint_magnetic(SDL_Window * window);

void place_player(SDL_Window * window);

void place_shoot(SDL_Window * window);

void print_score(SDL_Window * window);
