#include "window.h"
#include "sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

SDL_Window* create_window()
{
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);

	my_font = TTF_OpenFont("assets/text.ttf", 30);

	SDL_Window* window =  SDL_CreateWindow("Vectrex Minestorm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 900, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderClear(renderer);

	return window;
}

void destroy_window(SDL_Window* window)
{
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(SDL_GetRenderer(window));
	SDL_DestroyWindow(window);
}
