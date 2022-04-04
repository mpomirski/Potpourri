#include "Level.h"
Level::Level(Vector2D player_starting_position, const char* enemy_sprite, Vector<Vector2D> enemy_positions, const char* background_sprite, Vector<const char*> enemy_patterns) {
	player = new Player("./resources/character.bmp", res, "player");
	player->position = player_starting_position;
	//Default starting position: { LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2 }

	//Default bg: "./resources/background.bmp"
	background = res->LoadSprite(background_sprite);
	if (background == NULL) { throw "Background loading error"; }

	//Default enemy sprite "./resources/enemy.bmp"
	for (int i = 0; i < enemy_positions.getLength(); i++) {
		SDL_assert(enemy_positions.getLength() == enemy_patterns.getLength());
		Enemy* enemy = new Enemy(enemy_sprite, res, "enemy", enemy_patterns[i]);
		enemy->position = enemy_positions[i];
		enemies.push(enemy);
	}
}

//When using this constructor, make sure to set background, enemies and player!
Level::Level() {
}