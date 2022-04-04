#pragma once
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "drawing.h"
#include "vector.h"
#include "hud.h"
#include "Object.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "Player.h"
#include "FileLoader.h"
#include "ResourceHandler.h"
#include "Timer.h"
#include "Level.h"

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"



#define _USE_MATH_DEFINES
#define FULLSCREEN false
#define SCREEN_WIDTH 640 //pixels
#define SCREEN_HEIGHT 480 //pixels

#define LEVEL_WIDTH 1280 //pixels
#define LEVEL_HEIGHT 960 //pixels

//Velocity added to Player during movement
#define PLAYER_VELOCITY_FACTOR 1.5

class Game {
private:
	Timer* mTimer;
	InputHandler* inputH;
	const int FRAME_RATE = 120;
	SDL_Event mEvent;
	SDL_Surface* background;
	Hud* hud;
	Level current_level;
	int current_level_no;
	int previous_level_no = 0;

public:
	SDL_Surface* screen;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	ResourceHandler* res = new ResourceHandler;
	SDL_Rect camera;
	Game();
	int gameInit(int level_no);
	int gameStart();
	int gameLoop();
	void restartGame();
	void endGame();

private:
	Player* player;
	Vector<Enemy*> enemies;
	Level loadLevel(int level_no);
	void updateCamera(Object* player);
	int render(float gameTime, bool skip_rendering_objects = false);
	void Exit();
};