#include <SDL2/SDL.h>
#include <stdio.h>

#include "defs.h"
#include "game.h"

int main(int argc, char** argv) {
	SDL_Window* window = SDL_CreateWindow("Cool", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	if (!window) {
		printf("Failed to initialize window");
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		printf("Failed to initialize renderer");
		return 1;
	}

	SDL_ShowCursor(SDL_DISABLE);

	Game* game = new Game(renderer);

	while (!SDL_QuitRequested()) {
		game->handleInput();
		game->update();
		game->draw();
	}

	return 0;
}