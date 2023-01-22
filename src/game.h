#pragma once
#include <SDL2/SDL.h>
#include "entity/player.h"

class Game {
	public:
		Game(SDL_Renderer* renderer);
		void update();
		void draw();
		void handleInput();
	private:
		SDL_Renderer* renderer;
		Player* player;
		Uint64 now, last;
};