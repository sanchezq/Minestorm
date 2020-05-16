#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "enemy.h"

//Global

int g_level;

typedef enum
{
	E_GAME_MENU,
	E_GAME1_UPDATE,
	E_GAME2_UPDATE,
	E_GAME_PAUSE,
	E_GAME_SHUTDOWN
}E_GAME_STATE;

SDL_Event event;

int game_state;
int in_game_state;

bool gameOn;
bool rule_hitbox;
bool rule_pause;

int game_menu(SDL_Window* window);

int game_pause();

void game_shutdown(SDL_Window* window);

void game1_update(SDL_Window* window, float time);

void game2_update();

void game_loop(SDL_Window* window);

void game_level(SDL_Window* window);
void game_upgrade_level(SDL_Window* window);

const Uint8 *state;
