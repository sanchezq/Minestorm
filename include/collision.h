#pragma once

#include "enemy.h"
#include "shoot.h"
#include "player.h"

#include <SDL2/SDL.h>

int algo_sat_1(int x1, int y1, int size_x, int size_y, int x3, int y3, int size2);

void collision_floating_shot(t_floating* mine, t_shoot* shoot, float time);
void collision_magnetic_shot(t_magnetic* mine, t_shoot* shoot, float time);
void collision_player_shot(t_player* player, t_shoot* shoot);
void collision_player_mines(t_player* player, float time);

void test_collision(float time);
