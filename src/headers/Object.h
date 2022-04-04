#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "ResourceHandler.h"
#include "Vector2D.h"
#include "InputHandler.h"
#include "drawing.h"

#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960

#define VELOCITY_FACTOR 0.9

class Object{
public:
	SDL_Surface* background;
	Vector2D position = { 0, 0 };
	Vector2D velocity = { 0, 0 };
	SDL_Rect collision_rect = { 0, 0 };
	int health = 0;
	bool isHit = false;

	Object();
	Object(const char* bg_filename, ResourceHandler* res, const char* name);
	void updatePos();
	void updatePos(Vector2D pos);
	void render(SDL_Surface* screen, SDL_Rect camera);
	void detectCollision(Object* collidor);
};

