#include "Player.h"
Player::Player(const char* bg_filename, ResourceHandler* res, const char* name) {
	health = PLAYER_MAX_HEALTH;
	background = res->LoadSprite(bg_filename);
	if (background == NULL) {
		throw "Couldn't load sprite";
	}
	SDL_SetColorKey(this->background, true, SDL_MapRGB(this->background->format, 0, 0, 0));
	background1 = background;
	background2 = res->LoadSprite("./resources/character2.bmp");
	SDL_SetColorKey(background2, true, SDL_MapRGB(this->background->format, 0, 0, 0));
}

void Player::shootAt(Vector2D shot_pos) {
	if (bullets.getLength() >= 0) { // Limit bullets
		Object* bullet = new Object("./resources/player-bullet.bmp", res, "playerbullet");
		bullet->position = this->position;
		bullet->velocity = shot_pos * Vector2D{2.0f, 2.0f};
		bullet->health = BULLET_HEALTH;
		bullets.push(bullet);
	}
}

void Player::updatePos() {
	this->position += this->velocity;

	//map bounds
	if ((this->position.y - background->h / 2) < 0 || (this->position.y + background->h / 2 > LEVEL_HEIGHT)) {
		this->position.y -= this->velocity.y;
	}
	if ((this->position.x - background->w / 2) < 0 || (this->position.x + background->w / 2 > LEVEL_WIDTH)) {
		this->position.x -= this->velocity.x;
	}

	this->velocity *= {VELOCITY_FACTOR, VELOCITY_FACTOR};

	for (int i = 0; i < bullets.getLength(); i++) {
		if (bullets[i]->health > 0)
			bullets[i]->updatePos();
		else
			bullets.pop(i);
	}

	collision_rect.x = this->position.x;
	collision_rect.y = this->position.y;
	collision_rect.w = this->background->w;
	collision_rect.h = this->background->h;

}


void Player::render(SDL_Surface* screen, SDL_Rect camera) {
	DrawSurface(screen, this->background, this->position.x - camera.x, this->position.y - camera.y);
	for (int i = 0; i < bullets.getLength(); i++) {
		if (bullets[i]->health > 0) {
			bullets[i]->render(screen, camera);
			bullets[i]->health -= 1;
		}
		else
			bullets.pop(i);
	}
}

void Player::detectBulletCollision(Object* collidor) {
	for (int i = 0; i < bullets.getLength(); i++) {
		bullets[i]->detectCollision(collidor);
	}
}