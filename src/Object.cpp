#include "Object.h"
Object::Object(const char* bg_filename, ResourceHandler* res, const char* name) {
	background = res->LoadSprite(bg_filename);
	if (background == NULL) {
		throw "Couldn't load sprite";
	}
	SDL_SetColorKey(this->background, true, SDL_MapRGB(this->background->format, 0, 0, 0));
}
Object::Object(){}
void Object::updatePos() {
	this->position += this->velocity;

	collision_rect.x = this->position.x;
	collision_rect.y = this->position.y;
	collision_rect.w = this->background->w;
	collision_rect.h = this->background->h;
}

void Object::render(SDL_Surface* screen, SDL_Rect camera) {
	DrawSurface(screen, this->background, this->position.x - camera.x, this->position.y - camera.y);
}

void Object::detectCollision(Object* collidor) {
	if (SDL_HasIntersection(&this->collision_rect, &collidor->collision_rect) && collidor->isHit == false) {
		this->health -= 1000;
		collidor->health -= 1000;
		collidor->isHit = true;
	}
}