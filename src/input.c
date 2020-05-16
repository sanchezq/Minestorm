#include "input.h"
#include "window.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "sprite.h"
#include "shoot.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int check_input_menu(SDL_Window* window)
{
	if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
	{
		return E_GAME_SHUTDOWN;
	}

	else if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_f:
				g_shot_delay = SHOT_DELAY + 1;
				spawnpoint_init(window);
				floating_init(window);
				init_player(window);
				shoot_init();
				g_level = 0;
				g_enemy = (FLOATING + FLOATING_FIRE)*7;
				return E_GAME1_UPDATE;

			case SDLK_k:
				return E_GAME2_UPDATE;

			default:
				return E_GAME_MENU;
		}
	}
	return E_GAME_MENU;
}

int check_input_pause()
{
	if(event.type == SDL_QUIT)
	{
		rule_pause = false;
		shoot_destroy();
		floating_destroy();
		magnetic_destroy();
		floating_spawnpoint_destroy();
		magnetic_spawnpoint_destroy();
		player_destroy();
		return E_GAME_SHUTDOWN;
	}

	if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				rule_pause = false;
				shoot_destroy();
				floating_destroy();
				magnetic_destroy();
				floating_spawnpoint_destroy();
				magnetic_spawnpoint_destroy();
				player_destroy();
				g_level = 0;
				return E_GAME_MENU;

			case SDLK_SPACE:
				rule_pause = false;
				return E_GAME1_UPDATE;

			default:
				return E_GAME_PAUSE;
		}
	}
	return E_GAME_PAUSE;
}

void check_input_player_move()
{
	if(state[SDL_SCANCODE_R])
	{
		t_player* player = player_head;
		player->speed = MAX_SPEED;
	}
}

int check_input_player_turn()
{
	if(state[SDL_SCANCODE_D])
		return E_PLAYER_LEFT;

	if(state[SDL_SCANCODE_G])
		return E_PLAYER_RIGHT;

	return E_PLAYER_NOTHING;
}

int check_input_player()
{
	if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_e:
				return E_PLAYER_TP;

			case SDLK_t:
				return E_PLAYER_TP;

			case SDLK_c:
				return E_PLAYER_HITBOX;

			default:
				return E_PLAYER_NOTHING;
		}
	}
	return E_PLAYER_NOTHING;
}

int check_input_player_shoot()
{
	if(state[SDL_SCANCODE_F] && g_shot_delay > SHOT_DELAY)
	{
		g_shot_delay = 0;
		return E_PLAYER_SHOOT;
	}
	return E_PLAYER_NOTHING;
}

int check_input_in_game()
{
	if(event.type == SDL_QUIT)
	{
		shoot_destroy();
		floating_destroy();
		magnetic_destroy();
		floating_spawnpoint_destroy();
		magnetic_spawnpoint_destroy();
		player_destroy();
		return E_GAME_SHUTDOWN;
	}

	if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				shoot_destroy();
				floating_destroy();
				magnetic_destroy();
				floating_spawnpoint_destroy();
				magnetic_spawnpoint_destroy();
				player_destroy();
				g_level = 0;
				return E_GAME_MENU;

			case SDLK_SPACE:
				rule_pause = true;
				return E_GAME_PAUSE;

			default:
				return E_GAME1_UPDATE;
		}
	}
	return E_GAME1_UPDATE;
}

