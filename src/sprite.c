#include "sprite.h"
#include "window.h"
#include "enemy.h"
#include "game.h"
#include "player.h"
#include "shoot.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>

//Global Color
SDL_Color g_White = {255, 255, 255, 255};

void place_sprite(SDL_Window* window, SDL_Surface* surface, SDL_Rect spriteLoc, SDL_Rect rect)
{
	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_Texture* renderTEX = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_RenderCopy(renderer, renderTEX, &spriteLoc, &rect);
	
	SDL_DestroyTexture(renderTEX);
	SDL_FreeSurface(surface);
}

void place_background(SDL_Window * window)
{
	SDL_Rect backgroundRect;

	backgroundRect.w = WINDOW_W;
	backgroundRect.h = WINDOW_H;
	backgroundRect.x = 0;
	backgroundRect.y = 0;

	SDL_Surface* background = IMG_Load(BACKGROUNDSHEET_PATH);
	SDL_Rect spriteLoc = {0, 0, BACKGROUND_W, BACKGROUND_H};

	place_sprite(window, background, spriteLoc, backgroundRect);
}

void place_menu(SDL_Window * window)
{
	SDL_Rect menuRect;

	menuRect.w = WINDOW_W - BORDER_W*2;
	menuRect.h = WINDOW_H - BORDER_TOP - BORDER_BOT;
	menuRect.x = BORDER_W;
	menuRect.y = BORDER_TOP;

	SDL_Surface* background = IMG_Load(MENUSHEET_PATH);
	SDL_Rect spriteLoc = {0, 0, SPRITE_MENU_W, SPRITE_MENU_H};

	place_sprite(window, background, spriteLoc, menuRect);
}

void print_pause(SDL_Window * window)
{
	SDL_Rect pauseRect;

	pauseRect.w = WINDOW_W- BORDER_W*2;
	pauseRect.h = WINDOW_H - BORDER_BOT - BORDER_TOP;
	pauseRect.x = BORDER_W;
	pauseRect.y = BORDER_TOP;

	SDL_Surface* pause = IMG_Load(PAUSESHEET_PATH);
	SDL_Rect spriteLoc = {0, 0, SPRITE_PAUSE_W, SPRITE_PAUSE_H};
		
	place_sprite(window, pause, spriteLoc, pauseRect);
}

void print_life(SDL_Window * window)
{
	SDL_Rect lifeRect;

	lifeRect.w = WINDOW_W- BORDER_W*2;
	lifeRect.h = WINDOW_H - BORDER_BOT - BORDER_TOP;
	lifeRect.x = BORDER_W;
	lifeRect.y = BORDER_TOP;

	SDL_Surface* lifesheet = IMG_Load(LIFESHEET_PATH);
	SDL_Rect spriteLoc = {0, 0, SPRITE_LIFE_W, SPRITE_LIFE_H};
		
	place_sprite(window, lifesheet, spriteLoc, lifeRect);
}

void place_life_loose(SDL_Window * window)
{
	if(player_head == NULL)
		return;

	t_player* player = player_head;

	if(player->life<3)
	{
		SDL_Rect spriteLoc = {SPRITE_LIFE_LOOSE_X, SPRITE_LIFE_LOOSE_Y, SPRITE_LIFE_LOOSE_W, SPRITE_LIFE_LOOSE_W};

		SDL_Surface* spritesheet = IMG_Load(SPRITESHEET_PATH);

		SDL_Rect lifelooseRect;

		lifelooseRect.w = LIFE_LOOSE_W;
		lifelooseRect.h = LIFE_LOOSE_W;
		lifelooseRect.x = LIFE_LOOSE_X1;
		lifelooseRect.y = LIFE_LOOSE_Y;
	
		place_sprite(window, spritesheet, spriteLoc, lifelooseRect);

		if(player->life<2)
		{
			SDL_Surface* spritesheet = IMG_Load(SPRITESHEET_PATH);

			SDL_Rect lifelooseRect;

			lifelooseRect.w = LIFE_LOOSE_W;
			lifelooseRect.h = LIFE_LOOSE_W;
			lifelooseRect.x = LIFE_LOOSE_X2;
			lifelooseRect.y = LIFE_LOOSE_Y;
	
			place_sprite(window, spritesheet, spriteLoc, lifelooseRect);
		}
	}
}

void place_border(SDL_Window * window)
{
	SDL_Rect borderRect;

	borderRect.w = WINDOW_W;
	borderRect.h = WINDOW_H;
	borderRect.x = 0;
	borderRect.y = 0;

	SDL_Surface* border = IMG_Load(BORDERSHEET_PATH);
	SDL_Rect spriteLoc = {0, 0, BACKGROUND_W, BACKGROUND_H};
	
	place_sprite(window, border, spriteLoc, borderRect);
}

void renderer_show(SDL_Window * window)
{
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_RenderPresent(renderer);
}

void renderer_clear(SDL_Window * window)
{
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_RenderClear(renderer);
}

void place_floating(SDL_Window * window)
{
	if(floating_head == NULL)
		return;

	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_Surface* enemy = IMG_Load(SPRITESHEET_PATH);
	SDL_Texture* renderTEX = SDL_CreateTextureFromSurface(renderer, enemy);

	t_floating* mine = floating_head;
	while(mine != NULL)
	{
		int sprite_xpos = SPRITE_FLOATING_XPOS;

		SDL_Rect enemyRect;

		enemyRect.w = mine->size;
		enemyRect.h = mine->size;
		enemyRect.x = mine->xpos;
		enemyRect.y = mine->ypos;

		if(rule_hitbox == true)
			show_hitbox(window, enemyRect);

		if(mine->fireball == true)
			sprite_xpos=SPRITE_FLOATING_FIRE_XPOS;

		SDL_Rect spriteLoc = {sprite_xpos, SPRITE_MINES_YPOS, SPRITE_FLOATING_W, SPRITE_FLOATING_W};

		SDL_RenderCopy(renderer, renderTEX, &spriteLoc, &enemyRect);

		mine = mine->next;
	}
	SDL_DestroyTexture(renderTEX);
	SDL_FreeSurface(enemy);
}

void place_magnetic(SDL_Window * window)
{
	if(magnetic_head == NULL)
		return;

	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_Surface* enemy = IMG_Load(SPRITESHEET_PATH);
	SDL_Texture* renderTEX = SDL_CreateTextureFromSurface(renderer, enemy);

	t_magnetic* mine = magnetic_head;

	while(NULL != mine)
	{

		int sprite_xpos = SPRITE_MAGNETIC_XPOS;
		int sprite_ypos = SPRITE_MINES_YPOS;
		int size = SPRITE_MAGNETIC_W;

		SDL_Rect enemyRect;

		enemyRect.w = mine->size;
		enemyRect.h = mine->size;
		enemyRect.x = mine->xpos;
		enemyRect.y = mine->ypos;

		if(rule_hitbox == true)
			show_hitbox(window, enemyRect);

		if(mine->fireball == true)
		{
			sprite_xpos=SPRITE_MAGNETIC_FIRE_XPOS;
			sprite_ypos = SPRITE_MAGNETIC_FIRE_YPOS;
			size = SPRITE_MAGNETIC_FIRE_W;
		}
		
		SDL_Rect spriteLoc = {sprite_xpos, sprite_ypos, size, size};
		
		SDL_RenderCopy(renderer, renderTEX, &spriteLoc, &enemyRect);

		mine = mine->next;
	}

	SDL_DestroyTexture(renderTEX);
	SDL_FreeSurface(enemy);
}

void show_hitbox(SDL_Window * window, SDL_Rect rect)
{
	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderDrawRect(renderer, &rect);
}

void place_spawnpoint_floating(SDL_Window * window)
{
	if(spawn_head != NULL)
	{
		SDL_Renderer* renderer = SDL_GetRenderer(window);

		SDL_Surface* spawnmap = IMG_Load(SPRITESHEET_PATH);
		SDL_Texture* renderTEX = SDL_CreateTextureFromSurface(renderer, spawnmap);

		t_spawnpoint_floating* spawn = spawn_head;

		while(NULL != spawn)
		{
			SDL_Rect spawnRect;

			spawnRect.w = SPAWNPOINT_SIZE;
			spawnRect.h = SPAWNPOINT_SIZE;
			spawnRect.x = spawn->xpos;
			spawnRect.y = spawn->ypos;
	
			SDL_Rect spriteLoc = {SPRITE_SPAWNPOINT_XPOS, SPRITE_SPAWNPOINT_YPOS, SPRITE_SPAWNPOINT_W, SPRITE_SPAWNPOINT_W};
		
			SDL_RenderCopy(renderer, renderTEX, &spriteLoc, &spawnRect);

			spawn = spawn->next;
		}

		SDL_DestroyTexture(renderTEX);
		SDL_FreeSurface(spawnmap);
	}
}

void place_spawnpoint_magnetic(SDL_Window * window)
{
	if(spawn_head2 != NULL)
	{
		SDL_Renderer* renderer = SDL_GetRenderer(window);

		SDL_Surface* spawnmap = IMG_Load(SPRITESHEET_PATH);
		SDL_Texture* renderTEX = SDL_CreateTextureFromSurface(renderer, spawnmap);

		t_spawnpoint_magnetic* spawn = spawn_head2;

		while(NULL != spawn)
		{
			SDL_Rect spawnRect;

			spawnRect.w = SPAWNPOINT_SIZE;
			spawnRect.h = SPAWNPOINT_SIZE;
			spawnRect.x = spawn->xpos;
			spawnRect.y = spawn->ypos;
	
			SDL_Rect spriteLoc = {SPRITE_SPAWNPOINT_XPOS, SPRITE_SPAWNPOINT_YPOS, SPRITE_SPAWNPOINT_W, SPRITE_SPAWNPOINT_W};
		
			SDL_RenderCopy(renderer, renderTEX, &spriteLoc, &spawnRect);

			spawn = spawn->next;
		}

		SDL_DestroyTexture(renderTEX);
		SDL_FreeSurface(spawnmap);
	}
}

void place_player(SDL_Window * window)
{
	if(player_head != NULL)
	{
		SDL_Renderer* renderer = SDL_GetRenderer(window);

		t_player* player = player_head;

		SDL_Rect playerRect;

		playerRect.w = PLAYER_W;
		playerRect.h = PLAYER_H;
		playerRect.x = player->xpos;
		playerRect.y = player->ypos;

		if(rule_hitbox == true)
			show_hitbox_player(window);

		SDL_Surface* playermap = IMG_Load(SPRITESHEET_PATH);
		SDL_Texture* renderTEX = SDL_CreateTextureFromSurface(renderer, playermap);

		SDL_Rect spriteLoc = {SPRITE_PLAYER_XPOS, SPRITE_PLAYER_YPOS, SPRITE_PLAYER_W, SPRITE_PLAYER_H};
		
		SDL_RenderCopyEx(renderer, renderTEX, &spriteLoc, &playerRect, player->angle, NULL, SDL_FLIP_NONE);
		
		SDL_DestroyTexture(renderTEX);
		SDL_FreeSurface(playermap);
	}
}

void show_hitbox_player(SDL_Window* window)
{
	if(player_head == NULL)
		return;

	t_player* player = player_head;

	float x1, x2, x3, x4, y1, y2, y3, y4;

	x1 = player->xpos + PLAYER_W/2 + (PLAYER_W/2 * cos((player->angle) * M_PI / 180)) - (PLAYER_H/2 * sin((player->angle) * M_PI / 180));
	x2 = player->xpos + PLAYER_W/2 + (PLAYER_W/2 * cos((player->angle) * M_PI / 180)) - (-PLAYER_H/2 * sin((player->angle) * M_PI / 180));
	x3 = player->xpos + PLAYER_W/2 + (-PLAYER_W/2 * cos((player->angle) * M_PI / 180)) - (-PLAYER_H/2 * sin((player->angle) * M_PI / 180));
	x4 = player->xpos + PLAYER_W/2 + (-PLAYER_W/2 * cos((player->angle) * M_PI / 180)) - (PLAYER_H/2 * sin((player->angle) * M_PI / 180));

	y1 = player->ypos + PLAYER_H/2 + (PLAYER_W/2 * sin((player->angle) * M_PI / 180)) + (PLAYER_H/2 * cos((player->angle) * M_PI / 180));
	y2 = player->ypos + PLAYER_H/2 + (PLAYER_W/2 * sin((player->angle) * M_PI / 180)) + (-PLAYER_H/2 * cos((player->angle) * M_PI / 180));
	y3 = player->ypos + PLAYER_H/2 + (-PLAYER_W/2 * sin((player->angle) * M_PI / 180)) + (-PLAYER_H/2 * cos((player->angle) * M_PI / 180));
	y4 = player->ypos + PLAYER_H/2 + (-PLAYER_W/2 * sin((player->angle) * M_PI / 180)) + (PLAYER_H/2 * cos((player->angle) * M_PI / 180));

	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
	SDL_RenderDrawLine(renderer, x3, y3, x4, y4);
	SDL_RenderDrawLine(renderer, x4, y4, x1, y1);
}

void place_shoot(SDL_Window * window)
{
	if(shoot_head == NULL)
		return;

	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_Surface* shootmap = IMG_Load(SPRITESHEET_PATH);
	SDL_Texture* renderTEX = SDL_CreateTextureFromSurface(renderer, shootmap);

	t_shoot* shoot = shoot_head;

	int xpos;

	while(NULL != shoot)
	{
		SDL_Rect shootRect;

		shootRect.w = SHOT_SIZE;
		shootRect.h = SHOT_SIZE;
		shootRect.x = shoot->xpos;
		shootRect.y = shoot->ypos;

		if(rule_hitbox == true)
			show_hitbox(window, shootRect);

		xpos = SPRITE_SHOT_PLAYER_XPOS;

		if(shoot->player == false)
			xpos = SPRITE_SHOT_ENEMY_XPOS;
		
		SDL_Rect spriteLoc = {xpos, SPRITE_SHOT_YPOS, SPRITE_SHOT_W, SPRITE_SHOT_W};

		SDL_RenderCopy(renderer, renderTEX, &spriteLoc, &shootRect);

		shoot = shoot->next;
	}

	SDL_DestroyTexture(renderTEX);
	SDL_FreeSurface(shootmap);
}

void print_score(SDL_Window * window)
{
	if(player_head == NULL)
		return;

	t_player* player = player_head;

	SDL_Renderer* renderer = SDL_GetRenderer(window);

	sprintf(str_score, "SCORE: %i", player->score);

	SDL_Rect score_rect = {WINDOW_W/2 - SCORE_W/2, WINDOW_H - BORDER_BOT/2 - SCORE_H/8, SCORE_W, SCORE_H};

	SDL_Surface* surface = TTF_RenderText_Solid(my_font, str_score, g_White);
	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);

	SDL_DestroyTexture(score_texture);
}
