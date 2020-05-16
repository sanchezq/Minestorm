#include "collision.h"
#include "enemy.h"
#include "shoot.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int algo_sat_1(int x1, int y1, int size_x, int size_y, int x3, int y3, int size2)
{
	int x, x2, x4, y, y2, y4, collide;

	x2 = x1 + size_x;
	y2 = y1 + size_y;

	x4 = x3 + size2;
	y4 = y3 + size2;

	collide = 0;

	if(x2>x4)
	{
		x = x1-x4;
		if(x<=0)
			collide++;
	}
	else
	{
		x = x3-x2;
		if(x<=0)
			collide++;
	}

	if(y2>y4)
	{
		y = y1-y4;
		if(y<=0)
			collide++;
	}
	else
	{
		y = y3-y2;
		if(y<=0)
			collide++;
	}
	return collide;
}

void collision_floating_shot(t_floating* mine, t_shoot* shoot, float time)
{
	int x1, y1, x3, y3, size_x, size_y, size2, collide;
	bool fire;

	x1 = mine->xpos;
	y1 = mine->ypos;
	x3 = shoot->xpos;
	y3 = shoot->ypos;
	size_x = mine->size;
	size_y = size_x;
	size2 = SHOT_SIZE;

	collide = algo_sat_1(x1, y1, size_x, size_y, x3, y3, size2);

	if(collide == 2)
	{
		floating_die(mine, time, fire = true);
		shoot_touch(shoot);
	}
}

void collision_magnetic_shot(t_magnetic* mine, t_shoot* shoot, float time)
{
	int x1, y1, x3, y3, size_x, size_y, size2, collide;
	bool fire;

	x1 = mine->xpos;
	y1 = mine->ypos;
	x3 = shoot->xpos;
	y3 = shoot->ypos;
	size_x = mine->size;
	size_y = size_x;
	size2 = SHOT_SIZE;

	collide = algo_sat_1(x1, y1, size_x, size_y, x3, y3, size2);

	if(collide == 2)
	{
		magnetic_die(mine, time, fire = true);
		shoot_touch(shoot);
	}
}

void collision_player_shot(t_player* player, t_shoot* shoot)
{
	int x1, y1, x3, y3, size_x, size_y, size2, collide;

	x1 = player->xpos;
	y1 = player->ypos;
	x3 = shoot->xpos;
	y3 = shoot->ypos;
	size_x = PLAYER_W;
	size_y = PLAYER_H;
	size2 = SHOT_SIZE;

	collide = algo_sat_1(x1, y1, size_x, size_y, x3, y3, size2);

	if(collide == 2)
	{
		player->life --;
		shoot_touch(shoot);
	}
}

void collision_shot_shot(t_shoot* shot, t_shoot* shot2)
{
	int x1, y1, x3, y3, size_x, size_y, size2, collide;

	x1 = shot->xpos;
	y1 = shot->ypos;
	x3 = shot2->xpos;
	y3 = shot2->ypos;
	size_x = SHOT_SIZE;
	size_y = SHOT_SIZE;
	size2 = SHOT_SIZE;

	collide = algo_sat_1(x1, y1, size_x, size_y, x3, y3, size2);

	if(collide == 2)
	{
		shoot_touch(shot);
		shoot_touch(shot2);
	}
}

void collision_player_mines(t_player* player, float time)
{
	int x1, y1, x3, y3, size_x, size_y, size2, collide;
	bool fire;

	x1 = player->xpos;
	y1 = player->ypos;
	size_x = PLAYER_W;
	size_y = PLAYER_H;

	t_floating* floating = floating_head;
	t_magnetic* magnetic = magnetic_head;

	while(NULL != floating)
	{
		x3 = floating->xpos;
		y3 = floating->ypos;
		size2 = floating->size;

		collide = algo_sat_1(x1, y1, size_x, size_y, x3, y3, size2);

		if(collide == 2)
		{
			player->life --;
			floating_die(floating, time, fire = false);
		}

		floating = floating->next;
	}

	while(NULL != magnetic)
	{
		x3 = magnetic->xpos;
		y3 = magnetic->ypos;
		size2 = magnetic->size;

		collide = algo_sat_1(x1, y1, size_x, size_y, x3, y3, size2);

		if(collide == 2)
		{
			player->life --;
			magnetic_die(magnetic, time, fire = false);
		}

		magnetic = magnetic->next;
	}
}	

void test_collision(float time)
{
	t_shoot* shot = shoot_head;
	t_player* player = player_head;

	while(NULL != shot)
	{
		t_floating* floating = floating_head;
		t_magnetic* magnetic = magnetic_head;
		t_shoot* shot2 = shoot_head;

		while(NULL != floating)
		{
			collision_floating_shot(floating, shot, time);
			floating = floating->next;
		}

		while(NULL != magnetic)
		{
			collision_magnetic_shot(magnetic, shot, time);
			magnetic = magnetic->next;
		}

		while(NULL != shot2)
		{
			if(shot != shot2)
				collision_shot_shot(shot, shot2);
			shot2 = shot2->next;
		}

		collision_player_shot(player, shot);
		shot = shot->next;
	}
	collision_player_mines(player, time);
}
