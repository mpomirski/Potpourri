#include "InputHandler.h"
// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)

InputHandler* InputHandler::sInstance = NULL;

InputHandler* InputHandler::Instance() {
	if (sInstance == NULL)
		sInstance = new InputHandler();
	return sInstance;
}

void InputHandler::Release() {
	delete sInstance;
	sInstance = NULL;
}

InputHandler::InputHandler() {
}

InputHandler::~InputHandler() {

}

bool InputHandler::KeyDown(SDL_Scancode scanCode) {
	return mKeyboardStates[scanCode];
}

void InputHandler::Update() {
	SDL_PumpEvents();
	mKeyboardStates = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
}