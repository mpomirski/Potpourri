#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "vector.h"
#include "Enemy.h"
#include "Player.h"
#include "ResourceHandler.h"

class Level {
private:
	ResourceHandler* res = new ResourceHandler;
public:
	Player* player;
	Vector<Enemy*> enemies;
	SDL_Surface* background;
	Level();
	Level(Vector2D player_starting_position, const char* enemy_sprite,
		  Vector<Vector2D> enemy_positions, const char* background_sprite, Vector<const char*> enemy_patterns);
};