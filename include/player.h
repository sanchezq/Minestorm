#pragma once

#include "enemy.h"

#include <SDL2/SDL.h>

#define LIFE 3

#define PLAYER_W 44
#define PLAYER_H 24

#define MAX_SPEED 300
#define ROTATION_SPEED 400
#define DECREASE_SPEED 300

typedef enum
{
	E_PLAYER_LEFT,
	E_PLAYER_RIGHT,
	E_PLAYER_MOVE,
	E_PLAYER_TP,
	E_PLAYER_SHOOT,
	E_PLAYER_HITBOX,
	E_PLAYER_NOTHING
}E_PLAYER_INPUT;

typedef struct s_player
{
	int life;
	int xpos;
	int ypos;
	int angle;
	int score;
	float speed;
	struct s_player * player;

}t_player;

t_player* player_head;

void move_player(float time);

void turn_player(int turn, float time);

void shoot_player(int shoot, float time);

void input_player(int input);
void player_destroy();

void init_player(SDL_Window * window);

void tp_player();

int check_player_life();

void score_add_floating(t_floating* mine);
void score_add_magnetic(t_magnetic* mine);
