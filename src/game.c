#include "game.h"
#include "window.h"
#include "input.h"
#include "player.h"
#include "sprite.h"
#include "enemy.h"
#include "shoot.h"
#include "collision.h"

#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdio.h>

int game_menu(SDL_Window* window)
{
	place_menu(window);

	while(SDL_PollEvent(&event))
	{
		return check_input_menu(window);
	}
	return E_GAME_MENU;
}

void game_shutdown(SDL_Window* window)
{
	destroy_window(window);
	return;
}

int game_pause()
{
	while(rule_pause == true)
	{
		while(SDL_PollEvent(&event))
		{
			return check_input_pause();
		}
	}
	return E_GAME_PAUSE;
}

void game_level(SDL_Window* window)
{
	if(g_enemy==0)
	{
		g_level++;
		game_upgrade_level(window);
	}
}

void game_upgrade_level(SDL_Window* window)
{
	shoot_destroy();

	g_shot_delay = SHOT_DELAY + 1;
	init_player(window);
	shoot_init();

	if(g_level == 1)
	{
		floating_destroy();
		spawnpoint2_init(window);
		magnetic_init(window);
		g_enemy = (MAGNETIC + MAGNETIC_FIRE)*7;
	}
	else if(g_level == 2)
	{
		magnetic_destroy();
		spawnpoint_init(window);
		spawnpoint2_init(window);
		floating_init(window);
		magnetic_init(window);
		g_enemy = (FLOATING + FLOATING_FIRE + MAGNETIC + MAGNETIC_FIRE)*7;
	}
	else
	{
		magnetic_destroy();
		spawnpoint_init(window);
		spawnpoint2_init(window);
		floating_init(window);
		magnetic_init(window);
		game_state = E_GAME_MENU;
	}
}

void game1_update(SDL_Window * window, float time)
{
	floating_move(time);
	magnetic_move(time);
	move_player(time);
	move_shoot();
	shoot_alive();
	test_collision(time);

	place_spawnpoint_floating(window);
	place_spawnpoint_magnetic(window);
	place_shoot(window);
	place_player(window);
	place_floating(window);
	place_magnetic(window);
	print_life(window);
	place_life_loose(window);
	place_border(window);
	print_score(window);

	check_input_player_move();
	turn_player(check_input_player_turn(), time);
	shoot_player(check_input_player_shoot(), time);

	game_level(window);
	game_state = check_player_life();

	while(SDL_PollEvent(&event))
	{ 
		input_player(check_input_player());
		game_state = check_input_in_game(window);
	}

	if(g_shot_delay <= SHOT_DELAY)
		g_shot_delay ++;

	return;			
}

void game2_update()
{
	printf("Game Update 2 players\n");
	printf("Game Mode Missing\n");
	game_state = E_GAME_MENU;
	printf("Game Menu\n");
	return;
}

void game_loop(SDL_Window* window)
{
	gameOn = true;
	rule_hitbox = false;
	rule_pause = false;
	game_state = E_GAME_MENU;

	state = SDL_GetKeyboardState(NULL);

	Uint32 current_time;
	Uint32 previous_time = 0;
	float time;

	while(gameOn)
	{
		current_time = SDL_GetTicks();
		time = (current_time - previous_time) / 1000.0;
		previous_time = current_time;

		renderer_clear(window);
		place_background(window);

		switch(game_state)
		{
			case E_GAME_MENU:
				game_state = game_menu(window);
				break;

			case E_GAME1_UPDATE:
				game1_update(window, time);
				break;

			case E_GAME2_UPDATE:
				game2_update();
				break;

			case E_GAME_PAUSE:
				game_state = game_pause();
				break;

			case E_GAME_SHUTDOWN:
				gameOn = false;
				break;

			default:
				break;
		}

		if(rule_pause == true)
		{
			place_spawnpoint_floating(window);
			place_shoot(window);
			place_player(window);
			place_floating(window);
			place_magnetic(window);
			print_life(window);
			place_life_loose(window);
			print_pause(window);
			place_border(window);
			print_score(window);
		}

		renderer_show(window);
	}
	return;
}
