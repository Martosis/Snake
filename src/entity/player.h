#pragma once
#include "../vector.h"
#include "berry.h"
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_set>

#define MOVE_DISTANCE 32
#define MOVE_DELAY 10
#define PLAYER_SIZE 32
#define PLAYER_TEXTURE_PATH "res/cube.png"

class Player {
	public:
		Player(SDL_Renderer* renderer);
		void update(double deltaTime);
		void draw();
	private:
		void handleInput(double deltaTime);

		SDL_Renderer* renderer;
		SDL_Texture* texture;

		Vector2f pos = { 0, 0 }, direction = { 1, 0 }, lastDirection = { 0, 0 };

		std::vector<Vector2f>* lastLocations = new std::vector<Vector2f>();
		int size = 10;

		void addLocation(Vector2f vector);
		void die();
		void move();
		bool checkCollision();
		bool checkBerryCollision();
		
		inline bool canMove();

		void loadTexture();

		Uint8* keyboard;

		double timeSinceMove = 0;

		Berry* berry;
};