#include "player.h"
#include "game.h"
#include "window.h"
#include "input.h"
#include "sprite.h"
#include "shoot.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void move_player(float time)
{
	t_player* player = player_head;

	player->xpos += cos((player->angle) * M_PI / 180) * player->speed * time;
	player->ypos += sin((player->angle) * M_PI / 180) * player->speed * time;

	player->speed -= DECREASE_SPEED * time;

	if(player->speed < 0)
		player->speed = 0;

	int xpos_center = player->xpos + (PLAYER_W / 2);
	int ypos_center = player->ypos + (PLAYER_H / 2);
	
	if(xpos_center > WINDOW_W-BORDER_W)
		player->xpos = BORDER_W-(PLAYER_W / 2);
	else if(xpos_center < BORDER_W)
		player->xpos = WINDOW_W-(BORDER_W*2)+ PLAYER_W;

	if(ypos_center > WINDOW_H-BORDER_BOT)
		player->ypos = BORDER_TOP-(PLAYER_H / 2);
	else if(ypos_center < BORDER_TOP)
		player->ypos = WINDOW_H-BORDER_BOT-(PLAYER_H / 2);
}

void turn_player(int turn, float time)
{
	if(turn != E_PLAYER_NOTHING)
	{
		t_player* player = player_head;

		if(turn == E_PLAYER_LEFT)
		{
			player->angle -= ROTATION_SPEED * time;

			if(player->angle < 0)
				player->angle = 360-ROTATION_SPEED * time;
		}

		if(turn == E_PLAYER_RIGHT)
		{
			player->angle += ROTATION_SPEED * time;

			if(player->angle > 360)
				player->angle = ROTATION_SPEED * time;
		}
	}
}

void shoot_player(int shoot, float time)
{
	if(shoot == E_PLAYER_SHOOT)
		add_shoot_player(time);
}


void input_player(int input)
{
	if(input != E_PLAYER_NOTHING)
	{
		if(input == E_PLAYER_HITBOX)
		{
			if(rule_hitbox == true)
			{
				rule_hitbox = false;
			}
			else
			{
				rule_hitbox = true;
			}
		}

		if(input == E_PLAYER_TP)
		{
			tp_player();
		}
	}
}

void init_player(SDL_Window * window)
{
	t_player* player = malloc(sizeof(t_player));

	player_head = player;

	player->life = LIFE;
	player->xpos = (WINDOW_W / 2) - (PLAYER_W / 2);
	player->ypos = (WINDOW_H / 2) - (PLAYER_H / 2);
	player->angle = 0;
	player->speed = 0;
	player->score = 0;

	place_player(window);
}

void player_destroy()
{
	t_player* player = player_head;

	player_head = NULL;

	free(player);
}

void tp_player()
{
	t_player* player = player_head;

	player->xpos = (rand() % (WINDOW_W-BORDER_W-SIZE_3 + 1 -(SIZE_3+BORDER_W))) + SIZE_3+BORDER_W;
	player->ypos = (rand() % (WINDOW_H-BORDER_BOT-SIZE_3 + 1 -(SIZE_3+BORDER_TOP))) + SIZE_3+BORDER_TOP;
}

int check_player_life()
{
	t_player* player = player_head;

	if(player->life <= 0)
	{
		shoot_destroy();
		floating_destroy();
		magnetic_destroy();
		floating_spawnpoint_destroy();
		magnetic_spawnpoint_destroy();
		player_destroy();
		g_level = 0;
		return E_GAME_MENU;
	}
	return E_GAME1_UPDATE;
}

void score_add_floating(t_floating* mine)
{
	t_player* player = player_head;

	if(mine->size == SIZE_3)
	{
		if(mine->fireball == true)
			player->score += 325;
		else
			player->score += 100;
	}
	else if(mine->size == SIZE_2)
	{
		if(mine->fireball == true)
			player->score += 360;
		else
			player->score += 135;
	}
	else
	{
		if(mine->fireball == true)
			player->score += 425;
		else
			player->score += 200;
	}
}

void score_add_magnetic(t_magnetic* mine)
{
	t_player* player = player_head;

	if(mine->size == SIZE_3)
	{
		if(mine->fireball == true)
			player->score += 750;
		else
			player->score += 500;
	}
	else if(mine->size == SIZE_2)
	{
		if(mine->fireball == true)
			player->score += 785;
		else
			player->score += 535;
	}
	else
	{
		if(mine->fireball == true)
			player->score += 850;
		else
			player->score += 600;
	}
}
