#include "Enemy.h"


Enemy::Enemy(void){}
Enemy::Enemy(const char* filename, ResourceHandler* res, const char* name, const char* using_pattern) {
	mTimer = Timer::Instance();

	background = res->LoadSprite(filename);
	if (background == NULL) { throw "Couldn't load sprite"; }

	//Define black background as alpha
	SDL_SetColorKey(this->background, true, SDL_MapRGB(this->background->format, 0, 0, 0)); 

	this->health = ENEMY_HEALTH;
	this->pattern_name = using_pattern;
	background1 = background;
	background2 = res->LoadSprite("./resources/enemy2.bmp");
	//Define black background as alpha
	SDL_SetColorKey(background2, true, SDL_MapRGB(this->background->format, 0, 0, 0));
}


Enemy::~Enemy() {
	delete res;
}

void Enemy::render(SDL_Surface* screen, SDL_Rect camera, float time) {
	DrawSurface(screen, this->background, this->position.x - camera.x, this->position.y - camera.y);
	for (int i = 0; i < bullets.getLength(); i++) {
		if (bullets[i]->health > 0) {
			bullets[i]->velocity = Bullet::pattern(time, this->pattern_name, BULLET_WAVE_COUNT, i) * Vector2D { BULLET_VELOCITY_FACTOR, BULLET_VELOCITY_FACTOR };
			bullets[i]->updatePos();
			bullets[i]->render(screen, camera);
			bullets[i]->health -= 1;
		}
		else
			bullets.pop(i);
	}
}

void Enemy::shoot(float time) {
	if (bullets.getLength() >= 0){ // limit bullets
		Object* bullet = new Object("./resources/bullet.bmp", res, "bullet");
		bullet->position = Bullet::pattern(time, this->pattern_name, BULLET_WAVE_COUNT, bullets.getLength(), 4, this->position);
		bullet->velocity = Bullet::pattern(time, this->pattern_name, BULLET_WAVE_COUNT, bullets.getLength()) * Vector2D { BULLET_VELOCITY_FACTOR, BULLET_VELOCITY_FACTOR };
		bullet->health = BULLET_HEALTH;
		bullets.push(bullet);
	}
}

void Enemy::updatePos() {
	this->position += this->velocity;

	//map bounds
	if ((this->position.y - background->h / 2) < 0 || (this->position.y + background->h / 2 > LEVEL_HEIGHT)) {
		this->position.y -= this->velocity.y;
	}
	if ((this->position.x - background->w / 2) < 0 || (this->position.x + background->w / 2 > LEVEL_WIDTH)) {
		this->position.x -= this->velocity.x;
	}

	collision_rect.x = this->position.x;
	collision_rect.y = this->position.y;
	collision_rect.w = this->background->w;
	collision_rect.h = this->background->h;
}

void Enemy::detectBulletCollision(Object* collidor) {
	for (int i = 0; i < bullets.getLength(); i++) {
		bullets[i]->detectCollision(collidor);
	}
}