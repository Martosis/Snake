#include "berry.h"
#include <cstdlib>
#include <SDL2\SDL_image.h>
#include "../defs.h"

Berry::Berry(SDL_Renderer* renderer) {
	spawn();

	this->renderer = renderer;
	texture = IMG_LoadTexture(renderer, "res/berry.png");
}

void Berry::spawn() {
	pos.x = rand() % (WIDTH / 32) * 32;
	pos.y = rand() % (HEIGHT / 32) * 32;
}

void Berry::draw() {
	SDL_Rect rect = { (int) pos.x, (int) pos.y, BERRY_SIZE, BERRY_SIZE };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

Vector2f Berry::getPosition() {
	return pos;
}