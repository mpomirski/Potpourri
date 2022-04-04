#include "hud.h"

Hud::Hud(ResourceHandler* resHandler, SDL_Renderer* renderer) {
	res = resHandler;
	this->renderer = renderer;
	background = res->LoadSprite("./resources/hud.bmp");
	if (background == NULL) {
		printf("Hud sprite not found");
		throw "Hud sprite not found";
	}
	//Load Charset
	if (loadCharset() == 1) {
		throw "Charset not loaded properly!";
	}
	menu = res->LoadSprite("./resources/menu.bmp");
}

int Hud::loadCharset() {
	charset = res->LoadSprite("./resources/cs8x8.bmp");
	if (charset == NULL) {
		return 1;
	}
	SDL_SetColorKey(charset, true, 0x000000);
	return 0;
} 

void Hud::renderHud(SDL_Surface* screen, int x, int y) {
	DrawSurface(screen, background, x, y, 0);
}

SDL_Surface* Hud::getBgSurface() {
	return background;
}

void Hud::showTimer(float time) {
	SDL_Point position = { TIMER_POSITION_X, ELEMENT_POSITION_Y};
	int width = ELEMENT_WIDTH;
	int height = ELEMENT_HEIGHT;

	int bgColor = SDL_MapRGB(background->format, 0x8c, 0xe0, 0xcc);

	DrawRectangle(background, position.x, position.y, width, height, bgColor, bgColor);
	char text[128];
	sprintf(text, "Time: %.1lf s", time);
	DrawString(background, position.x, position.y, text, charset);
}

SDL_Surface* Hud::getCharset() {
	return charset;
};

void Hud::showHealth(Player* player, int czerwony, int czarny) {
	SDL_Point position = { HEALTHBAR_POSITION_X, ELEMENT_POSITION_Y };
	int width = ELEMENT_WIDTH;
	int height = ELEMENT_HEIGHT;
	char text[128];
	int bgColor = SDL_MapRGB(background->format, 0x8c, 0xe0, 0xcc);

	DrawRectangle(background, position.x, 0, width, height+10, bgColor, bgColor);
	DrawRectangle(background, position.x, position.y, ((float)(player->health) / PLAYER_MAX_HEALTH) * width, height, czarny, czerwony);
	sprintf(text, "Health: %i", (int)(float(player->health) * 100 / PLAYER_MAX_HEALTH));
	DrawString(background, position.x, position.y - 20, text, charset);
}

void Hud::showMenu(SDL_Surface* game_background) {
	DrawSurface(game_background, menu, 0, 0, 0);
}