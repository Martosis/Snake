#include "game.h"

Game::Game(SDL_Renderer* renderer) {
	this->renderer = renderer;
	player = new Player(renderer);
	now = SDL_GetPerformanceCounter();
	last = 0;
}

void Game::update() {
	SDL_PumpEvents();

	last = now;
	now = SDL_GetPerformanceCounter();

	double deltaTime = (now - last) * 1000 / (double) SDL_GetPerformanceFrequency();

	player->update(deltaTime);
}

void Game::draw() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	player->draw();
	SDL_RenderPresent(renderer);
}

void Game::handleInput() {
	SDL_Event event;
	
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				SDL_Quit();
				break;
			default: break;
		}
	}
}