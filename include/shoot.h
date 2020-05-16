#pragma once

#define SHOT_START 30
#define SHOT_SIZE 10
#define SHOT_LIFETIME 20

#define PLAYER_SHOT_SPEED 400
#define ENEMY_SHOT_SPEED 100

#define SHOT_DELAY 5

#include <stdbool.h>

//Global
int g_shot_delay;

typedef struct s_shoot_list
{
	struct s_shoot * head;
	struct s_shoot * tail;
}t_shoot_list;

t_shoot_list* shoot_list_head;

typedef struct s_shoot
{
	int xpos;
	int ypos;
	int xmove;
	int ymove;
	int angle;
	int speed;
	int lifetime;
	bool player;
	struct s_shoot * next;
	struct s_shoot * prev;

}t_shoot;

t_shoot* shoot_head;

void shoot_init();

void add_shoot_player(float time);
void add_shoot_enemy(float time, int x, int y);

void move_shoot();
void move_fireball(t_shoot* shoot);

void shoot_alive();

void shoot_touch(t_shoot* shoot);

void shoot_destroy();
