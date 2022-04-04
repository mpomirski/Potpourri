#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include <string.h>
#include <stdio.h>
#include "vector.h"

class ResourceHandler{
public:
	Vector<SDL_Surface*> sprite_array;
	Vector<SDL_Texture*> texture_array;
	SDL_Surface* LoadSprite(const char* source);
	SDL_Texture* LoadTexture(const char* source, SDL_Renderer* renderer);

};

