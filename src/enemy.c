#include "enemy.h"
#include "window.h"
#include "sprite.h"
#include "player.h"
#include "game.h"
#include "shoot.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void spawnpoint_init(SDL_Window * window)
{
	g_spawn_num = (FLOATING + FLOATING_FIRE)*7;

	t_spawnpoint_list * list = malloc(sizeof(t_spawnpoint_list));

	list->head = NULL;
	list->tail = NULL;

	list->num = g_spawn_num;

	spawn_head_list = list;

	for(int i = 0; i < g_spawn_num; i++)
	{
		create_spawnpoint_floating(list);
	}

	place_spawnpoint_floating(window);
}

void spawnpoint2_init(SDL_Window * window)
{
	g_spawn_num2 = (MAGNETIC + MAGNETIC_FIRE)*7;

	t_spawnpoint_list2 * list = malloc(sizeof(t_spawnpoint_list2));

	list->head = NULL;
	list->tail = NULL;

	list->num = g_spawn_num2;

	spawn_head_list2 = list;

	for(int i = 0; i < g_spawn_num2; i++)
	{
		create_spawnpoint_magnetic(list);
	}

	place_spawnpoint_magnetic(window);
}

void create_spawnpoint_floating(t_spawnpoint_list * list)
{
	t_spawnpoint_floating * list_spawn = malloc(sizeof(t_floating));

	if(list->head == NULL)
	{
		spawn_head = list_spawn;
		list->head = list_spawn;
		list->tail = list_spawn;
	}
	else
	{
		list_spawn->prev = list->tail;
		list_spawn->prev->next = list_spawn;
		list->tail = list_spawn;
	}

	list_spawn->next = NULL;

	list_spawn->xpos = (rand() % (WINDOW_W-BORDER_W-SIZE_3 + 1 -(SIZE_3+BORDER_W))) + SIZE_3+BORDER_W;
	list_spawn->ypos = (rand() % (WINDOW_H-BORDER_BOT-SIZE_3 + 1 -(SIZE_3+BORDER_TOP))) + SIZE_3+BORDER_TOP;
}

void create_spawnpoint_magnetic(t_spawnpoint_list2 * list)
{
	t_spawnpoint_magnetic * list_spawn = malloc(sizeof(t_magnetic));

	if(list->head == NULL)
	{
		spawn_head2 = list_spawn;
		list->head = list_spawn;
		list->tail = list_spawn;
	}
	else
	{
		list_spawn->prev = list->tail;
		list_spawn->prev->next = list_spawn;
		list->tail = list_spawn;
	}

	list_spawn->next = NULL;

	list_spawn->xpos = (rand() % (WINDOW_W-BORDER_W-SIZE_3 + 1 -(SIZE_3+BORDER_W))) + SIZE_3+BORDER_W;
	list_spawn->ypos = (rand() % (WINDOW_H-BORDER_BOT-SIZE_3 + 1 -(SIZE_3+BORDER_TOP))) + SIZE_3+BORDER_TOP;
}

void floating_init(SDL_Window * window)
{
	t_mines_floating * list = malloc(sizeof(t_mines_floating));

	list->head = NULL;
	list->tail = NULL;

	list->num = FLOATING + FLOATING_FIRE;
	floating_list_head = list;

	int size = SIZE_3;
	int speed = MINE_SPEED_3;

	for(int i = 0; i < list->num; i++)
	{
		create_floating(i, list, size, speed);
	}

	place_floating(window);
}

void magnetic_init(SDL_Window * window)
{
	t_mines_magnetic * list = malloc(sizeof(t_mines_magnetic));

	list->head = NULL;
	list->tail = NULL;

	list->num = MAGNETIC + MAGNETIC_FIRE;
	magnetic_list_head = list;

	int size = SIZE_3;
	int speed = MINE_SPEED_3;

	for(int i = 0; i < list->num; i++)
	{
		create_magnetic(i, list, size, speed);
	}

	place_magnetic(window);
}

void create_floating(int floating, t_mines_floating * list, int size, int speed)
{
	int neg;

	t_floating * list_mines = malloc(sizeof(t_floating));

	if(floating_head == NULL)
	{
		floating_head = list_mines;
		list->head = list_mines;
		list->tail = list_mines;
		list_mines->prev = NULL;
	}
	else
	{
		list_mines->prev = list->tail;
		list_mines->prev->next = list_mines;
		list_mines->next = NULL;
		list->tail = list_mines;
	}

	t_spawnpoint_floating* spawn = spawn_head;

	list_mines->speed = speed;
	list_mines->fireball = false;
	list_mines->size = size;

	list_mines->xpos = spawn->xpos - (list_mines->size / 2) + (SPAWNPOINT_SIZE / 2);
	list_mines->ypos = spawn->ypos - (list_mines->size / 2) + (SPAWNPOINT_SIZE / 2);

	if(spawn->next != NULL)
	{
		spawn->next->prev = NULL;
		spawn_head = spawn->next;
	}
	else
	{
		spawn_head = NULL;
	}

	free(spawn);

	list_mines->xmove = (rand() % FLOATING_DIRECTION)+ list_mines->speed;
	list_mines->ymove = (rand() % FLOATING_DIRECTION)+ list_mines->speed;

	neg = rand() % 2;
	if(neg==1)
		list_mines->xmove *= -1;

	neg = rand() % 2;
	if(neg==1)
		list_mines->ymove *= -1;

	if(floating<FLOATING_FIRE)
	{
		list_mines->fireball = true;
	}
}

void create_magnetic(int magnetic, t_mines_magnetic * list, int size, int speed)
{
	t_magnetic * list_mines = malloc(sizeof(t_magnetic));

	if(magnetic_head == NULL)
	{
		magnetic_head = list_mines;
		list->head = list_mines;
		list->tail = list_mines;
		list_mines->prev = NULL;
	}
	else
	{
		list_mines->prev = list->tail;
		list_mines->prev->next = list_mines;
		list_mines->next = NULL;
		list->tail = list_mines;
	}

	t_spawnpoint_magnetic* spawn = spawn_head2;

	list_mines->speed = speed;
	list_mines->fireball = false;
	list_mines->size = size;

	list_mines->xpos = spawn->xpos - (list_mines->size / 2) + (SPAWNPOINT_SIZE / 2);
	list_mines->ypos = spawn->ypos - (list_mines->size / 2) + (SPAWNPOINT_SIZE / 2);

	if(spawn->next != NULL)
		spawn->next->prev = NULL;
	spawn_head2 = spawn->next;
	spawn->next = NULL;
	free(spawn);

	list_mines->xmove = 0;
	list_mines->ymove = 0;
	list_mines->angle = 0;

	if(magnetic<MAGNETIC_FIRE)
	{
		list_mines->fireball = true;
	}
}

void floating_move(float time)
{
	int xpos_center;
	int ypos_center;

	t_floating* mine = floating_head;

	while(NULL != mine)
	{
		mine->xpos += mine->xmove * time;
		mine->ypos += mine->ymove * time;

		xpos_center = mine->xpos + (mine->size / 2);
		ypos_center = mine->ypos + (mine->size / 2);

		if(xpos_center > WINDOW_W-BORDER_W)
			mine->xpos = BORDER_W-(mine->size / 2);
		else if(xpos_center < BORDER_W)
			mine->xpos = WINDOW_W-(BORDER_W*2) + mine->size/2;

		if(ypos_center > WINDOW_H-BORDER_BOT)
			mine->ypos = BORDER_TOP-(mine->size / 2);
		else if(ypos_center < BORDER_TOP)
			mine->ypos = WINDOW_H-BORDER_BOT-(mine->size / 2);

		mine = mine->next;
	}
}

void magnetic_move(float time)
{
	t_magnetic* mine = magnetic_head;
	t_player* player = player_head;

	float Xc, Yc, X2c, Y2c, X, Y, distance_left_x, distance_right_x, distance_up_y, distance_down_y;

	while(NULL != mine)
	{
		Xc = mine->xpos + mine->size/2;
		Yc = mine->ypos + mine->size/2;

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
			mine->xpos+= mine->speed*time*2;
		}
		else if(X<0)
		{
			mine->xpos-= mine->speed*time;
		}

		if(X>0 && distance_right_x > abs(X))
		{
			mine->xpos-= mine->speed*time;
		}
		else if(X>0)
		{
			mine->xpos+= mine->speed*time*2;
		}

		if(Y<0 && distance_up_y > abs(Y))
		{
			mine->ypos+= mine->speed*time*2;
		}
		else if(Y<0)
		{
			mine->ypos-= mine->speed*time;
		}

		if(Y>0 && distance_down_y > abs(Y))
		{
			mine->ypos-= mine->speed*time;
		}
		else if(Y>0)
		{
			mine->ypos+= mine->speed*time*2;
		}

		if(Xc > WINDOW_W-BORDER_W)
			mine->xpos = BORDER_W-(mine->size / 2);
		else if(Xc < BORDER_W)
			mine->xpos = WINDOW_W-(BORDER_W*2) + mine->size/2;

		if(Yc > WINDOW_H-BORDER_BOT)
			mine->ypos = BORDER_TOP-(mine->size / 2);
		else if(Yc < BORDER_TOP)
			mine->ypos = WINDOW_H-BORDER_BOT-(mine->size / 2);

		mine = mine->next;
	}
}

void floating_die(t_floating* mine, float time, bool fire_shoot)
{
	t_mines_floating * list = floating_list_head;

	if(mine->next != NULL && mine->prev != NULL)
	{
		mine->next->prev = mine->prev;
		mine->prev->next = mine->next;
	}
	else if(mine->prev == NULL && mine->next == NULL)
	{
		list->head = NULL;
		list->tail = NULL;
		floating_head = NULL;
	}
	else if(mine->prev == NULL)
	{
		list->head = mine->next;
		floating_head = mine->next;
		mine->next->prev = NULL;
	}
	else if(mine->next == NULL)
	{
		list->tail = mine->prev;
		mine->prev->next = NULL;
	}

	mine->next = NULL;
	mine->prev = NULL;

	int size, fireball, speed;
	size = SIZE_2;
	fireball = 0;
	speed = MINE_SPEED_2;

	if(mine->size != SIZE_1)
	{
		if(mine->size == SIZE_2)
			size = SIZE_1;

		if(mine->fireball == true)
			fireball = FLOATING_FIRE;

		if(mine->speed == MINE_SPEED_2)
			speed = MINE_SPEED_1;

		create_floating(fireball, floating_list_head, size, speed);
		create_floating(fireball, floating_list_head, size, speed);
	}

	if(mine->fireball == true && fire_shoot == true)
		add_shoot_enemy(time, mine->xpos, mine->ypos);

	score_add_floating(mine);

	g_enemy--;

	free(mine);
}

void magnetic_die(t_magnetic* mine, float time, bool fire_shoot)
{
	t_mines_magnetic * list = magnetic_list_head;

	if(mine->next != NULL && mine->prev != NULL)
	{
		mine->next->prev = mine->prev;
		mine->prev->next = mine->next;
	}
	else if(mine->prev == NULL && mine->next == NULL)
	{
		list->head = NULL;
		list->tail = NULL;
		magnetic_head = NULL;
	}
	else if(mine->prev == NULL)
	{
		list->head = mine->next;
		magnetic_head = mine->next;
		mine->next->prev = NULL;
	}
	else if(mine->next == NULL)
	{
		list->tail = mine->prev;
		mine->prev->next = NULL;
	}

	mine->next = NULL;
	mine->prev = NULL;

	int size, fireball, speed;
	size = SIZE_2;
	fireball = 0;
	speed = MINE_SPEED_2;

	if(mine->size != SIZE_1)
	{
		if(mine->size == SIZE_2)
			size = SIZE_1;

		if(mine->fireball == true)
			fireball = FLOATING_FIRE;

		if(mine->speed == MINE_SPEED_2)
			speed = MINE_SPEED_1;

		create_magnetic(fireball, magnetic_list_head, size, speed);
		create_magnetic(fireball, magnetic_list_head, size, speed);
	}

	if(mine->fireball == true && fire_shoot == true)
		add_shoot_enemy(time, mine->xpos, mine->ypos);

	score_add_magnetic(mine);

	g_enemy--;

	free(mine);
}

void floating_destroy()
{
	if(floating_list_head != NULL)
	{
		t_floating* mine = floating_head;
		t_mines_floating* list = floating_list_head;

		list->head = NULL;

		floating_list_head = NULL;
	
		while(mine != list->tail && mine != NULL)
		{
			mine->next->prev = NULL;
			floating_head = mine->next;
			mine->next = NULL;
			free(mine);

			mine = floating_head;
		}
	
		list->tail = NULL;
		floating_head = NULL;
		free(mine);
	}
}

void magnetic_destroy()
{
	if(magnetic_list_head != NULL)
	{
		t_magnetic* mine = magnetic_head;
		t_mines_magnetic* list = magnetic_list_head;

		list->head = NULL;

		magnetic_list_head = NULL;
	
		while(mine != list->tail && mine != NULL)
		{
			mine->next->prev = NULL;
			magnetic_head = mine->next;
			mine->next = NULL;
			free(mine);

			mine = magnetic_head;
		}
	
		list->tail = NULL;
		magnetic_head = NULL;
		free(mine);
	}
}

void floating_spawnpoint_destroy()
{
	if(spawn_head != NULL)
	{
		t_spawnpoint_floating* mine = spawn_head;
		t_spawnpoint_list* list = spawn_head_list;

		list->head = NULL;

		spawn_head_list = NULL;
	
		while(mine != list->tail && mine != NULL)
		{
			mine->next->prev = NULL;
			spawn_head = mine->next;
			mine->next = NULL;
			free(mine);

			mine = spawn_head;
		}
	
		list->tail = NULL;
		spawn_head_list = NULL;
		free(mine);
	}
}

void magnetic_spawnpoint_destroy()
{
	if(spawn_head2 != NULL)
	{
		t_spawnpoint_magnetic* mine = spawn_head2;
		t_spawnpoint_list2* list = spawn_head_list2;

		list->head = NULL;

		spawn_head_list2 = NULL;
	
		while(mine != list->tail && mine != NULL)
		{
			mine->next->prev = NULL;
			spawn_head2 = mine->next;
			mine->next = NULL;
			free(mine);

			mine = spawn_head2;
		}
	
		list->tail = NULL;
		spawn_head2 = NULL;
		free(mine);
	}
}
