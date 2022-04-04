#include "Bullet.h"
Bullet::Bullet(const char* filename, ResourceHandler* res) {
	background = res->LoadSprite(filename);
	if (background == NULL) {
		throw "Couldn't load sprite";
	}
	SDL_SetColorKey(this->background, true, SDL_MapRGB(this->background->format, 0, 0, 0));
}
Bullet::Bullet() {}

Vector2D Bullet::pattern(float time, const char* p_name, int wave_length, int bullet_index, int factor, Vector2D init_position) {
	if (!strcmp(p_name, "circle")) {
		return Vector2D{ init_position.x + (float)cos((2 * M_PI) / wave_length * bullet_index + time) / factor, \
						 init_position.y + (float)sin(2 * M_PI / wave_length * bullet_index + time) / factor };
	}
	else if (!strcmp(p_name, "complex")) {
		return Vector2D{ init_position.x + (float)cos((2 * M_PI + bullet_index) / wave_length * bullet_index) / factor, \
						 init_position.y + (float)sin(2 * M_PI / wave_length * bullet_index) / factor };
	}
	else if (!strcmp(p_name, "altsphere")) {
		return Vector2D{ init_position.x + (float)sin((M_PI) / wave_length * bullet_index) / factor, \
						 init_position.y + (float)cos(M_PI / wave_length * bullet_index) / factor };
	}
	else if (!strcmp(p_name, "custom1")) {
		return Vector2D{ init_position.x + (float)sin((M_PI * 3) / wave_length * bullet_index) / factor, \
				 init_position.y + (float)sin(M_PI / wave_length * bullet_index) / factor };
	}
	else if (!strcmp(p_name, "custom2")) {
		return Vector2D{ init_position.x + (float)sin((M_PI) / wave_length * bullet_index) / factor, \
				 init_position.y + (float)sin(M_PI + 0.5 / wave_length * bullet_index) / factor };
	}
}