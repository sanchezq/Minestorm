#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define WINDOW_W 640
#define WINDOW_H 900
#define BORDER_W 64
#define BORDER_TOP 92
#define BORDER_BOT 104

#define SCORE_W 300
#define SCORE_H 60

//Global Font
TTF_Font* my_font;

SDL_Window* create_window();

void destroy_window(SDL_Window* window);

