#pragma once
#include "Object.h"
#include "Vector2D.h"
class Bullet : public Object{
public:
	Bullet::Bullet(const char* filename, ResourceHandler* res);
	Bullet::Bullet();
	static Vector2D pattern(float time, const char* p_name, int wave_length, int bullet_index, int factor = 4, Vector2D init_position = { 0, 0 });
};

