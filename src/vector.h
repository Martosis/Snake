#pragma once

struct Vector2f {
	Vector2f(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2f() {
		this->x = 0;
		this->y = 0;
	}
	float x, y;

	bool operator==(const Vector2f& other) {
		return x == other.x && y == other.y;
	}
};