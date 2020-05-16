#include <SDL2/SDL.h>
#include <unistd.h>

#include "window.h"
#include "input.h"
#include "game.h"


int main()
{
	SDL_Window* window = create_window();
	game_loop(window);
	game_shutdown(window);

	return 0;
}
