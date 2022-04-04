#include "game.h"

	Game::Game() {
		int rc;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			printf("SDL_Init error: %s\n", SDL_GetError());
			throw "SDL_Init error";
		}

		rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
			&window, &renderer);

		if (FULLSCREEN) {
			//tryb pe³noekranowy / fullscreen mode
			rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
				&window, &renderer);
		}

		if (rc != 0) {
			SDL_Quit();
			printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
			throw "SDL_CreateWindowAndRenderer error";
		}

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_SetWindowTitle(window, "CatMeow 2021: Potpourri");
		SDL_Surface* icon = SDL_LoadBMP("./resources/icon.bmp");
		SDL_SetColorKey(icon, true, SDL_MapRGB(icon->format, 0, 0, 0));
		SDL_SetWindowIcon(window, icon);


		// wy³¹czenie widocznoœci kursora myszy
		SDL_ShowCursor(SDL_DISABLE);

		screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
			0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

		scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH, SCREEN_HEIGHT);

		this->camera = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , SCREEN_WIDTH, SCREEN_HEIGHT};

		mTimer = Timer::Instance();
		inputH = InputHandler::Instance();
	}

	void Game::endGame() {
		Exit();
	}

	void Game::restartGame() {
		gameInit(current_level_no);
		mTimer->Reset();
	}

	void Game::updateCamera(Object* player) {
		camera.x = player->position.x - SCREEN_WIDTH/2;
		camera.y = player->position.y - SCREEN_HEIGHT/2;

		//Checking boundaries
		if (camera.x < 0)
			camera.x = 0;
		if (camera.y < 0)
			camera.y = 0;

		if (camera.x > LEVEL_WIDTH - camera.w)
			camera.x = LEVEL_WIDTH - camera.w;
		if (camera.y > LEVEL_HEIGHT - camera.h)
			camera.y = LEVEL_HEIGHT - camera.h;
	}
	Level Game::loadLevel(int level_no) {
		switch (level_no) {
		default:
		//Main menu
		case 0: {
			Vector<Vector2D>* enemy_positions = new Vector<Vector2D>;
			Level main_menu;
			main_menu.background = res->LoadSprite("./resources/menu.bmp");
			main_menu.player = NULL;
			main_menu.enemies = NULL;
			return main_menu;
			break;
		}
		//Level 1
		case 1: {
			Vector<Vector2D> enemy_positions;
			Vector<const char*> enemy_patterns;
			enemy_patterns.push("circle");
			enemy_positions.push(Vector2D{ LEVEL_WIDTH / 2 + 100, LEVEL_HEIGHT / 2 });
			Level* level = new Level({ LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2 }, "./resources/enemy.bmp",\
									   enemy_positions, "./resources/background.bmp", enemy_patterns);
			return *level;
			break;
		}
		//Level 2
		case 2: {
			Vector<Vector2D>* enemy_positions = new Vector<Vector2D>;
			Vector<const char*> enemy_patterns;
			enemy_patterns.push("complex");
			enemy_positions->push(Vector2D{ LEVEL_WIDTH / 2 - 100, LEVEL_HEIGHT / 2 - 100 });
			Level* level = new Level({ LEVEL_WIDTH / 2 + 50, LEVEL_HEIGHT / 2 + 50 }, "./resources/enemy.bmp",\
									   *enemy_positions, "./resources/background2.bmp", enemy_patterns);
			return *level;
			break;
		}
		//Level 3
		case 3: {
			char* enemy_pattern_name = new char;

			FileLoader fl = FileLoader("./resources/level.catt");
			Level level = fl.loadLevel();
			//We need to copy the enemy_pattern_name string, so it would not be destroyed with the FileLoader object
			strcpy(enemy_pattern_name, level.enemies[0]->pattern_name);
			level.enemies[0]->pattern_name = enemy_pattern_name;

			return level;
			break;
		}
		//Death menu
		case 10: {
			Vector<Vector2D>* enemy_positions = new Vector<Vector2D>;
			Level* death_menu = new Level();
			death_menu->background = res->LoadSprite("./resources/death-menu.bmp");
			death_menu->player = NULL;
			death_menu->enemies = NULL;
			return *death_menu;
			break;
		}
		//Win menu
		case 11: {
			Vector<Vector2D>* enemy_positions = new Vector<Vector2D>;
			Level* win_menu = new Level();
			win_menu->background = res->LoadSprite("./resources/win-menu.bmp");
			win_menu->player = NULL;
			win_menu->enemies = NULL;
			return *win_menu;
			break; 
		}
		}
		throw "Couldn't load the selected level";
		return *new Level();
	}
	int Game::gameInit(int level_no) {
		this->hud = new Hud(res, renderer);
		current_level = loadLevel(level_no);
		current_level_no = level_no;
		player = current_level.player;
		background = current_level.background;
		enemies = current_level.enemies;

		gameLoop();
		return 0;
	}

	int Game::render(float gameTime, bool skip_rendering_objects) {
		//Colors used
		int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
		int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);

		this->camera.x = 0;
		this->camera.y = 0;

		if(!skip_rendering_objects)
			updateCamera(player);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_BlitSurface(background, &camera, screen, NULL);

		if (!skip_rendering_objects) {
			player->render(screen, camera);
			for (int i = 0; i < enemies.getLength(); i++)
				enemies[i]->render(screen, camera, gameTime);

			hud->showTimer(gameTime);
			hud->showHealth(player, czerwony, czarny);
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);

		if(!skip_rendering_objects)
			hud->renderHud(screen);

		SDL_RenderPresent(renderer);
		return 0;
	}

	int Game::gameLoop() {
		float gameTime = 0.0f;
		bool restart = false;
		bool quit = false;
		int nextLevel = -1;
		int frameCounter = 0;

		while (!quit) {
			mTimer->Update();
			inputH->Update();
			if (player == NULL){
				if (this->current_level_no == 0) { //Main menu
					if (inputH->KeyDown(SDL_SCANCODE_1)) { nextLevel = 1; quit = true; }
					if (inputH->KeyDown(SDL_SCANCODE_2)) { nextLevel = 2; quit = true; }
					if (inputH->KeyDown(SDL_SCANCODE_3)) { nextLevel = 3; quit = true; }
					if (inputH->KeyDown(SDL_SCANCODE_ESCAPE)) { quit = true; }
				}
				else if (this->current_level_no == 10) { // Game over menu
					if (inputH->KeyDown(SDL_SCANCODE_R)) { nextLevel = this->previous_level_no; quit = true; }
					if (inputH->KeyDown(SDL_SCANCODE_M)) { nextLevel = 0; quit = true; }
				}
				else if (this->current_level_no == 11) { //Win menu
					if (inputH->KeyDown(SDL_SCANCODE_R)) { nextLevel = this->previous_level_no; quit = true; }
					if (inputH->KeyDown(SDL_SCANCODE_N)) { 
						nextLevel = this->previous_level_no + 1; 
						if (this->previous_level_no == 3)
							nextLevel = 0;
						quit = true; 
					}
				}
				render(gameTime, true);
				gameTime += mTimer->DeltaTime();
				mTimer->Reset();
			}
			else if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {
				//Player movement - arrows
				if (inputH->KeyDown(SDL_SCANCODE_UP)) { player->velocity.y = -PLAYER_VELOCITY_FACTOR; }
				if (inputH->KeyDown(SDL_SCANCODE_DOWN)) { player->velocity.y = PLAYER_VELOCITY_FACTOR; }
				if (inputH->KeyDown(SDL_SCANCODE_RIGHT)) { player->velocity.x = PLAYER_VELOCITY_FACTOR; }
				if (inputH->KeyDown(SDL_SCANCODE_LEFT)) { player->velocity.x = -PLAYER_VELOCITY_FACTOR; }

				//Player shooting - WSAD
				if (frameCounter % 20 == 0) {
					if (inputH->KeyDown(SDL_SCANCODE_W)) { player->shootAt({ 0.0f, -1.0f }); }
					if (inputH->KeyDown(SDL_SCANCODE_S)) { player->shootAt({ 0.0f, 1.0f }); }
					if (inputH->KeyDown(SDL_SCANCODE_D)) { player->shootAt({ 1.0f, 0.0f }); }
					if (inputH->KeyDown(SDL_SCANCODE_A)) { player->shootAt({ -1.0f, 0.0f }); }
				}

				//Other input
				if (inputH->KeyDown(SDL_SCANCODE_N)) {
					restart = true;
					quit = true;
				}
				if (inputH->KeyDown(SDL_SCANCODE_ESCAPE)) { quit = true; }

				//Animations
				if ((int)player->velocity.x != 0 || (int)player->velocity.y != 0) {
					if ((frameCounter + 1) % 20 == 0) {
						if (player->background == player->background1)
							player->background = player->background2;
						else {
							player->background = player->background1;
						}
					}
				}

				player->updatePos();

				//Invincibility frames
				if ((frameCounter + 1) % 250 == 0) {
					player->isHit = false;
				}
				if (player->health <= 0) {
					nextLevel = 10;
					quit = true;
				}

				for (int i = 0; i < enemies.getLength(); i++) {
					if ((frameCounter + 1) % 150 == 0) {
						for (int j = 0; j < 10; j++) {
							enemies[i]->shoot(mTimer->DeltaTime());
						}
						if (this->current_level_no == 3) {
							enemies[i]->velocity += {(float)(rand() % 3 * 0.1 * pow(-1, rand() % 2)), (float)(rand() % 3 * 0.1 * pow(-1, rand() % 2))};
						}
					}
					if (enemies[i]->health <= 0) {
						nextLevel = 11;
						quit = true;
					}
	
					if ((int)ceil(enemies[i]->velocity.x) != 0 || (int)ceil(enemies[i]->velocity.y) != 0) {
						if ((frameCounter + 1) % 20 == 0) {
							if (enemies[i]->background == enemies[i]->background1)
								enemies[i]->background = enemies[i]->background2;
							else {
								enemies[i]->background = enemies[i]->background1;
							}
						}
					}
					enemies[i]->updatePos();
					enemies[i]->detectCollision(player);
					enemies[i]->detectBulletCollision(player);
					enemies[i]->isHit = false;
					player->detectBulletCollision(enemies[i]);
				}
				render(gameTime);

				gameTime += mTimer->DeltaTime();
				mTimer->Reset();
				frameCounter++;
			}
		}
		previous_level_no = this->current_level_no;
		if (restart) { restartGame(); }
		if (nextLevel != -1) { gameInit(nextLevel); }
		
		return 0;
	}

	int Game::gameStart() {
		gameInit(0);
		return 0;
	}

	void Game::Exit() {
		for (int i = 0; i < res->texture_array.getLength(); i++) {
			if (res->texture_array[i] != NULL) {
				SDL_DestroyTexture(res->texture_array[i]);
			}
		}
		for (int i = 0; i < res->texture_array.getLength(); i++) {
			if (res->sprite_array[i] != NULL) {
				SDL_FreeSurface(res->sprite_array[i]);
			}
		}

		delete(res);
		InputHandler::Release();
		inputH = NULL;

		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}


