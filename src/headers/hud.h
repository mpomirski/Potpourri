#pragma once
#include "drawing.h"
#include <string.h>
#include <stdio.h>
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "ResourceHandler.h"
#include "Timer.h"
#include "Player.h"

//All defines are in pixels
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define ELEMENT_POSITION_Y 20
#define ELEMENT_WIDTH 100
#define ELEMENT_HEIGHT 10
#define TIMER_POSITION_X 10
#define HEALTHBAR_POSITION_X 200


class Hud{
public:
	Hud(ResourceHandler* resHandler, SDL_Renderer* renderer);
	SDL_Surface* getCharset();
	SDL_Surface* getBgSurface();
	int loadCharset();
	void showTimer(float time);
	void renderHud(SDL_Surface* screen, int x = 0, int y = 0);
	void showHealth(Player* player, int czerwony, int czarny);
	void showMenu(SDL_Surface* game_background);

private:
	Timer* timer = Timer::Instance();
	SDL_Renderer* renderer;
	SDL_Surface* background;
	ResourceHandler* res;
	SDL_Surface* charset;
	SDL_Surface* menu;
};

