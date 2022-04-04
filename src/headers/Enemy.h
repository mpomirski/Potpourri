#pragma once
#define _USE_MATH_DEFINES
#include "Object.h"
#include "Timer.h"
#include "Bullet.h"

#define ENEMY_HEALTH 10000
#define BULLET_WAVE_COUNT 10
#define BULLET_VELOCITY_FACTOR 10
#define BULLET_HEALTH 1000

class Enemy : public Object{
private:
	ResourceHandler* res = new ResourceHandler;
	Vector<Object*> bullets;
	Timer* mTimer;
public:
	const char* pattern_name;
	SDL_Surface* background1;
	SDL_Surface* background2;
public:
	//Enemy::Enemy();
	Enemy::Enemy(void);
	Enemy::Enemy(const char* filename, ResourceHandler* res, const char* name, const char* using_pattern);
	Enemy::~Enemy();
	void shoot(float time);
	void render(SDL_Surface* screen, SDL_Rect camera, float time);
	void detectBulletCollision(Object* collidor);
	void updatePos();

};

