#include "shoot.h"
#include "player.h"
#include "window.h"

void shoot_init()
{
	t_shoot_list* shoot_list = malloc(sizeof(t_shoot_list));

	shoot_list->head = NULL;
	shoot_list->tail = NULL;

	shoot_list_head = shoot_list;

	return;
}

void add_shoot_player(float time)
{
	t_player* player = player_head;

	t_shoot_list* list = shoot_list_head;
	t_shoot* shoot = malloc(sizeof(t_shoot));

	if(list->head == NULL)
	{
		shoot_head = shoot;
		list->head = shoot;
		list->tail = shoot;
		shoot->prev = NULL;
	}
	else
	{
		shoot->prev = list->tail;
		shoot->prev->next = shoot;
		list->tail = shoot;
	}

	shoot->xmove = 0;
	shoot->ymove = 0;
	shoot->next = NULL;
	shoot->lifetime = SHOT_LIFETIME;
	shoot->player = true;
	shoot->angle = player->angle;

	shoot->xpos = ((player->xpos + PLAYER_W/2) + cos((player->angle) * M_PI / 180)*SHOT_START)- SHOT_SIZE;
	shoot->ypos = ((player->ypos + PLAYER_H/2) + sin((player->angle) * M_PI / 180)*SHOT_START)- SHOT_SIZE;

	shoot->speed = PLAYER_SHOT_SPEED * time;
}

void add_shoot_enemy(float time, int x, int y)
{
	t_player* player = player_head;

	t_shoot_list* list = shoot_list_head;
	t_shoot* shoot = malloc(sizeof(t_shoot));

	if(list->head == NULL)
	{
		shoot_head = shoot;
		list->head = shoot;
		list->tail = shoot;
		shoot->prev = NULL;
	}
	else
	{
		shoot->prev = list->tail;
		shoot->prev->next = shoot;
		list->tail = shoot;
	}

	shoot->xmove = 0;
	shoot->ymove = 0;
	shoot->next = NULL;
	shoot->lifetime = SHOT_LIFETIME;
	shoot->player = false;
	shoot->angle = player->angle;

	shoot->xpos = x+ SHOT_SIZE/2;
	shoot->ypos = y+ SHOT_SIZE/2;

	shoot->speed = ENEMY_SHOT_SPEED * time;

	move_fireball(shoot);
}

void move_shoot()
{
	t_shoot* shoot = shoot_head;

	int xpos_center;
	int ypos_center;

	while(NULL != shoot)
	{
		if(shoot->player == true)
		{
			shoot->xpos += cos((shoot->angle) * M_PI / 180) * shoot->speed;
			shoot->ypos += sin((shoot->angle) * M_PI / 180) * shoot->speed;
		}
		else
		{
			shoot->xpos += shoot->xmove;
			shoot->ypos += shoot->ymove;
		}

		xpos_center = shoot->xpos + SHOT_SIZE/2;
		ypos_center = shoot->ypos + SHOT_SIZE/2;

		if(xpos_center > WINDOW_W-BORDER_W)
			shoot->xpos = BORDER_W-(SHOT_SIZE / 2);
		else if(xpos_center < BORDER_W)
			shoot->xpos = WINDOW_W-(BORDER_W*2)+ SHOT_SIZE + PLAYER_W;

		if(ypos_center > WINDOW_H-BORDER_BOT)
			shoot->ypos = BORDER_TOP-(SHOT_SIZE / 2);
		else if(ypos_center < BORDER_TOP)
			shoot->ypos = WINDOW_H-BORDER_BOT-(SHOT_SIZE / 2);

		shoot->lifetime --;
		shoot = shoot->next;
	}
}

void move_fireball(t_shoot* shoot)
{
	t_player* player = player_head;

	float Xc, Yc, X2c, Y2c, X, Y, distance_left_x, distance_right_x, distance_up_y, distance_down_y;

	Xc = shoot->xpos + SHOT_SIZE/2;
	Yc = shoot->ypos + SHOT_SIZE/2;

	X2c = player->xpos + PLAYER_W/2;
	Y2c = player->ypos + PLAYER_H/2;

	distance_left_x = (Xc - BORDER_W) + (WINDOW_W - BORDER_W - X2c);
	distance_up_y = (Yc - BORDER_TOP) + (WINDOW_H - BORDER_BOT - Y2c);

	distance_right_x = (WINDOW_W - BORDER_W - Xc) + (X2c - BORDER_W);
	distance_down_y = (WINDOW_H - BORDER_BOT - Yc) + (Y2c - BORDER_TOP);

	X = Xc - X2c;
	Y = Yc - Y2c;

	if(X<0 && distance_left_x > abs(X))
	{
		shoot->xmove+= shoot->speed*2;
	}
	else if(X<0)
	{
		shoot->xmove-= shoot->speed;
	}

	if(X>0 && distance_right_x > abs(X))
	{
		shoot->xmove-= shoot->speed;
	}
	else if(X>0)
	{
		shoot->xmove+= shoot->speed*2;
	}

	if(Y<0 && distance_up_y > abs(Y))
	{
		shoot->ymove+= shoot->speed*2;
	}
	else if(Y<0)
	{
		shoot->ymove-= shoot->speed;
	}

	if(Y>0 && distance_down_y > abs(Y))
	{
		shoot->ymove-= shoot->speed;
	}
	else if(Y>0)
	{
		shoot->ymove+= shoot->speed*2;
	}
}

void shoot_alive()
{
	t_shoot* shoot = shoot_head;

	t_shoot_list* list = shoot_list_head;

	while(NULL != shoot)
	{
		if(shoot->lifetime < 0)
		{
			if(shoot->next != NULL)
			{
				shoot->next->prev = NULL;
				shoot_head = shoot->next;
				list->head = shoot->next;
				shoot->next = NULL;
			}
			else
			{
				shoot_head = NULL;
				list->head = NULL;
				list->tail = NULL;
			}
			free(shoot);
		}

		shoot = shoot->next;
	}
}

void shoot_touch(t_shoot* shoot)
{
	t_shoot_list * list = shoot_list_head;

	if(shoot->next != NULL && shoot->prev != NULL)
	{
		shoot->next->prev = shoot->prev;
		shoot->prev->next = shoot->next;
	}
	else if(shoot->prev == NULL && shoot->next == NULL)
	{
		list->head = NULL;
		list->tail = NULL;
		shoot_head = NULL;
	}
	else if(shoot->prev == NULL)
	{
		list->head = shoot->next;
		shoot_head = shoot->next;
		shoot->next->prev = NULL;
	}
	else if(shoot->next == NULL)
	{
		list->tail = shoot->prev;
		shoot->prev->next = NULL;
	}

	shoot->next = NULL;
	shoot->prev = NULL;

	free(shoot);
}

void shoot_destroy()
{
	if(shoot_list_head != NULL)
	{
		t_shoot* shoot = shoot_head;
		t_shoot_list* list = shoot_list_head;

		list->head = NULL;

		shoot_list_head = NULL;
	
		while(shoot != list->tail && shoot != NULL)
		{
			shoot->next->prev = NULL;
			shoot_head = shoot->next;
			shoot->next = NULL;
			free(shoot);

			shoot = shoot_head;
		}
	
		list->tail = NULL;
		shoot_head = NULL;
		free(shoot);
	}
}
