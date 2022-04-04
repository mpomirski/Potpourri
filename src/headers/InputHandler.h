#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include <iostream>
class InputHandler{
private:
	static InputHandler* sInstance;
	const Uint8* mKeyboardStates = SDL_GetKeyboardState(NULL);
public:
	static InputHandler* Instance();
	static void Release();
	bool KeyDown(SDL_Scancode scanCode);
	void Update();
private:
	InputHandler();
	~InputHandler();
};

