#include "player.h"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include "../defs.h"

Player::Player(SDL_Renderer* renderer) {
	this->renderer = renderer;
	loadTexture();

	addLocation(pos);

	berry = new Berry(renderer);
}

void Player::update(double deltaTime) {
	handleInput(deltaTime);

	timeSinceMove += deltaTime;

	if (canMove()) {
		move();

		if (checkCollision()) {
			die();
		}

		if (checkBerryCollision()) {
			berry->spawn();
			size++;
		}

		addLocation(pos);
	}
}

void Player::draw() {
	SDL_Rect rect = { 0, 0, PLAYER_SIZE, PLAYER_SIZE };

	for (Vector2f loc : *lastLocations) {
		rect.x = loc.x;
		rect.y = loc.y;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}

	berry->draw();
}

void Player::handleInput(double deltaTime) {
	keyboard = (Uint8*) SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_W] && lastDirection.y == 0) {
		direction.y = -1;
		direction.x = 0;
	}

	if (keyboard[SDL_SCANCODE_S] && lastDirection.y == 0) {
		direction.y = 1;
		direction.x = 0;
	}

	if (keyboard[SDL_SCANCODE_A] && lastDirection.x == 0) {
		direction.x = -1;
		direction.y = 0;
	}

	if (keyboard[SDL_SCANCODE_D] && lastDirection.x == 0) {
		direction.x = 1;
		direction.y = 0;
	}
}

void Player::addLocation(Vector2f vector) {
	lastLocations->insert(lastLocations->begin(), vector);
	//lastLocationsSet->insert(vector);

	if (lastLocations->size() > size) {
	//	lastLocationsSet->erase(lastLocations->back());
		lastLocations->pop_back();
	}
}

void Player::die() {
	size = 1;
	lastLocations->clear();
	pos = { 0, 0 };
	direction = { 1, 0 };
	lastDirection = { 0, 0 };
	berry->spawn();
	//lastLocationsSet->clear();
}

bool Player::checkCollision() {
	return pos.x + PLAYER_SIZE > WIDTH || pos.x < 0 || pos.y + PLAYER_SIZE > HEIGHT || pos.y < 0 || std::count(lastLocations->begin(), lastLocations->end(), pos);
}

bool Player::checkBerryCollision() {
	SDL_Rect playerLoc = { 0, 0, PLAYER_SIZE, PLAYER_SIZE };
	SDL_Rect berryLoc = { (int) berry->getPosition().x, (int) berry->getPosition().y, BERRY_SIZE, BERRY_SIZE };
		
	for (Vector2f loc : *lastLocations) {
		playerLoc.x = loc.x;
		playerLoc.y = loc.y;

		if (SDL_HasIntersection(&playerLoc, &berryLoc)) {
			return true;
		}
	}

	return false;
}

void Player::move() {
	timeSinceMove -= MOVE_DELAY;
	pos.x += direction.x * MOVE_DISTANCE;
	pos.y += direction.y * MOVE_DISTANCE;
	lastDirection = direction;
}

bool Player::canMove() {
	return timeSinceMove > MOVE_DELAY;
}

void Player::loadTexture() {
	texture = IMG_LoadTexture(renderer, PLAYER_TEXTURE_PATH);

	if (!texture) {
		SDL_Log("Failed to load player texture.");
	}
}