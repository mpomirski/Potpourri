#include "ResourceHandler.h"

SDL_Surface* ResourceHandler::LoadSprite(const char* source) {
	SDL_Surface* sprite = SDL_LoadBMP(source);
	if (!sprite) {
		printf("SDL_LoadBMP(%s) error: %s\n", source, SDL_GetError());
		throw "SpriteLoadError";
		return NULL;
	};
	sprite_array.push(sprite);

	return sprite;
}

SDL_Texture* ResourceHandler::LoadTexture(const char* source, SDL_Renderer* renderer) {
	SDL_Surface* texture_surface = LoadSprite(source);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, texture_surface);
	if (!texture) {
		texture_array.push(texture);
		return texture;
	}
	else
		return NULL;
}
