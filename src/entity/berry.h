#pragma once

#include <SDL2\SDL.h>
#include "../vector.h"

#define BERRY_SIZE 32

class Berry {
	public:
		Berry(SDL_Renderer* renderer);
		void spawn();
		void draw();
		Vector2f getPosition();
	private:
		Vector2f pos;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		int screenWidth, screenHeight;
};