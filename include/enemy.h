#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

#define	FLOATING 1
#define FLOATING_FIRE 1
#define MAGNETIC 1
#define MAGNETIC_FIRE 1

#define SIZE_3 50
#define SIZE_2 40
#define SIZE_1 30

#define MINE_SPEED_3 30
#define MINE_SPEED_2 40
#define MINE_SPEED_1 50

#define FLOATING_DIRECTION 50

//Global
int g_enemy;

typedef struct s_mines_floating
{
	int num;
	struct s_floating * head;
	struct s_floating * tail;

}t_mines_floating;

t_mines_floating* floating_list_head;

typedef struct s_floating
{
	int xpos;
	int ypos;
	int size;
	int xmove;
	int ymove;
	int speed;
	bool fireball;
	struct s_floating * next;
	struct s_floating * prev;

}t_floating;

t_floating* floating_head;

typedef struct s_mines_magnetic
{
	int num;
	struct s_magnetic * head;
	struct s_magnetic * tail;

}t_mines_magnetic;

t_mines_magnetic* magnetic_list_head;

typedef struct s_magnetic
{
	int xpos;
	int ypos;
	int size;
	int xmove;
	int ymove;
	int angle;
	int speed;
	bool fireball;
	struct s_magnetic * next;
	struct s_magnetic * prev;

}t_magnetic;

t_magnetic* magnetic_head;


typedef struct s_spawnpoint_list
{
	int num;
	struct s_spawnpoint_floating * head;
	struct s_spawnpoint_floating * tail;

}t_spawnpoint_list;

t_spawnpoint_list* spawn_head_list;

typedef struct s_spawnpoint_floating
{
	int xpos;
	int ypos;
	struct s_spawnpoint_floating * next;
	struct s_spawnpoint_floating * prev;

}t_spawnpoint_floating;

t_spawnpoint_floating* spawn_head;

typedef struct s_spawnpoint_list2
{
	int num;
	struct s_spawnpoint_magnetic * head;
	struct s_spawnpoint_magnetic * tail;

}t_spawnpoint_list2;

t_spawnpoint_list2* spawn_head_list2;

typedef struct s_spawnpoint_magnetic
{
	int xpos;
	int ypos;
	struct s_spawnpoint_magnetic * next;
	struct s_spawnpoint_magnetic * prev;

}t_spawnpoint_magnetic;

t_spawnpoint_magnetic* spawn_head2;

int g_spawn_num;
int g_spawn_num2;

void floating_init(SDL_Window* window);
void magnetic_init(SDL_Window* window);

void create_floating(int floating, t_mines_floating * list, int size, int speed);
void floating_move(float time);

void create_magnetic(int magnetic, t_mines_magnetic * list, int size, int speed);
void magnetic_move(float time);

void spawnpoint_init(SDL_Window * window);
void spawnpoint2_init(SDL_Window * window);

void create_spawnpoint_floating(t_spawnpoint_list * list);
void create_spawnpoint_magnetic(t_spawnpoint_list2 * list);

void floating_die(t_floating* mine, float time, bool fire_shoot);
void magnetic_die(t_magnetic* mine, float time, bool fire_shoot);

void floating_destroy();
void magnetic_destroy();

void floating_spawnpoint_destroy();
void magnetic_spawnpoint_destroy();
