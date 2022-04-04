#pragma once
#include "Object.h"
#define PLAYER_MAX_HEALTH 10000
#define BULLET_HEALTH 500

class Player : public Object {
private:
	ResourceHandler* res = new ResourceHandler;
	Vector<Object*> bullets;
public:
	SDL_Surface* background1;
	SDL_Surface* background2;

public:
	Player::Player(const char* bg_filename, ResourceHandler* res, const char* name);
	Player::Player();
	void updatePos();
	void shootAt(Vector2D shot_pos);
	void render(SDL_Surface* screen, SDL_Rect camera);
	void detectBulletCollision(Object* collidor);
};