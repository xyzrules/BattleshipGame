#include "Game.h"

using namespace std;

Game::Game() {
	cout << "START GAME" << endl;
}

Game::~Game() {
	cout << "END GAME" << endl;
	free();
}

void Game::free() {
	TTF_CloseFont(gFont);
	gFont = NULL;
	gButtonSpriteSheetTexture.free();
	gArrowSpriteSheetTexture.free();
	gChoiceSpriteSheetTexture.free();
	gBackgroundP1.free();
	gBackgroundP2.free();
	gGridSpriteSheetTexture.free();
	gPhaseText.free();
	gTransitionText.free();
	for (int i = 0; i < TOTAL_CHOICE;++i) {
		gText[i].free();
	}
}

bool Game::loadMedia(SDL_Renderer* &gRenderer) {
	//Load sprite sheet
	if (!gButtonSpriteSheetTexture.loadFromFile("_Playfield/button_outline.png", gRenderer)){
		printf("Failed to load button sprite texture!\n");
		return false;
	}
	//Load background
	else if (!gBackgroundP1.loadFromFile("_Playfield/P1.png", gRenderer)) {
		printf("Failed to load background image for P1!\n");
		return false;
	}
	else if (!gBackgroundP2.loadFromFile("_Playfield/P2.png", gRenderer)) {
		printf("Failed to load background image for P2!\n");
		return false;
	}
	//Load direction sprite sheet
	else if (!gArrowSpriteSheetTexture.loadFromFile("_Playfield/arrow.png", gRenderer)){
		printf("Failed to load button sprite texture!\n");
		return false;
	}
	//Load grid sprite sheet
	else if (!gGridSpriteSheetTexture.loadFromFile("_Playfield/grid_color.png", gRenderer)) {
		printf("Failed to load grid sprite texture!\n");
		return false;
	}
	else if (!gChoiceSpriteSheetTexture.loadFromFile("_Playfield/ingame_button.png", gRenderer)) {
		printf("Failed to load choices sprite texture!\n");
		return false;
	}
	else {
		//Open the font 
		gFont = TTF_OpenFont("_Menu/global_font.ttf", 42);
		if (gFont == NULL) {
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			return false;
		}
	}

	{
		//Set buttons size, sprites & position
		for (int i = 0;i < BOARD_SIDE;++i) {
			for (int j = 0;j < BOARD_SIDE;++j) {
				gButtons[i+1][j+1].setSize_Sprites(50, 50);
				gButtons[i+1][j+1].setPosition(50 + 51 * i, 50 + 51 * j);
			}
		}
		//Set arrow size, sprites & position
		for (int i = 0;i < TOTAL_ARROWS; ++i) {
			gArrow[i].setSize_Sprites(50, 50);
			if (i == UP_ARROW) gArrow[i].setPosition(675, 170);
			if (i == RIGHT_ARROW) gArrow[i].setPosition(725, 220);
			if (i == DOWN_ARROW) gArrow[i].setPosition(675, 270);
			if (i == LEFT_ARROW) gArrow[i].setPosition(625, 220);
		}
		//Set choice size, sprites & position
		for (int i = 0;i < TOTAL_CHOICE;++i) {
			gChoice[i].setSize_Sprites(200, 112);
			if (i == UNDO) gChoice[i].setPosition(600, 320);
			if (i == DONE) gChoice[i].setPosition(600, 420);
		}
		//Set grid size, sprites & position
		for (int i = 0;i < GRID_TOTAL_SPRITE;++i) {
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = i * 50;
			gSpriteClips[i].w = 50;
			gSpriteClips[i].h = 50;
		}
		for (int i = 0;i < BOARD_SIDE;++i) {
			for (int j = 0;j < BOARD_SIDE;++j) {
				GRID_WIDTH[i + 1][j + 1] = 50 + 51 * i;
				GRID_HEIGHT[i + 1][j + 1] = 50 + 51 * j;
				gridCurrentSprite[i][j] = SHIP_NONE;
			}
		}
		//Set ttf for buttons
		/*
		if (!gText[UNDO].loadFromRenderedText("UNDO", mColor, gRenderer, gFont)) {
			printf("Failed to load UNDO text!\n");
			return false;
		}
		*/
		if (!gText[DONE].loadFromRenderedText("DONE" , mColor, gRenderer, gFont)) {
			printf("Failed to load DONE text!\n");
			return false;
		}
	}
	return true;
}

bool Game::mainGame(int cpu, SDL_Renderer* &gRenderer) {
	sG P1, P2;

	if (!loadMedia(gRenderer)) {
		cout << "Failed to load media in game" << endl;
		return true;
	}
	else {
		//Help section for deploy phase
		//Transition scene add here
		turn = 1;
		if (transitionPhase(cpu, gRenderer, 0, 0) == QUIT_GAME) {
			return true;
		}
		cout << "P1 deploy phase" << endl;

		if (deployPhase(P1, 0, gRenderer) == QUIT_GAME) {
			return true;
		}
		//Transition scene add here
		turn = 2;
		if (cpu)	cout << "CPU deploy phase" << endl;
		else	cout << "P2 deploy phase" << endl;
		

		if (transitionPhase(cpu, gRenderer, 0, 0) == QUIT_GAME) {
			return true;
		}
		if (deployPhase(P2, cpu, gRenderer) == QUIT_GAME) {
			return true;
		}
		//Help section for battle phase
		

		while (true) {

			int quitGame = CONTINUE_TURN;
			//Transition scene add here
			turn = 1;
			quitGame = transitionPhase(cpu, gRenderer, 0, 1);
			//p1 turn
			do {
				quitGame = battlePhase(P2, 0, gRenderer);
				SDL_Delay(800);
			} while (quitGame == CONTINUE_TURN);

			if (!P2.continueGame()) {
				//Winning scene add here
				quitGame = transitionPhase(cpu, gRenderer, 1, 1);
				cout << "p1 wins\n";
				return false;
			}

			if (quitGame == QUIT_GAME)	return true;
			//Transition scene add here
			cout << endl << "Change Turn" << endl;
			turn = 2;
			quitGame = transitionPhase(cpu, gRenderer, 0, 1);

			//p2 turn
			do {
				quitGame = battlePhase(P1, cpu, gRenderer);
				SDL_Delay(800);
			} while (quitGame == CONTINUE_TURN);

			if (!P1.continueGame()) {
				//Winning scene add here
				quitGame = transitionPhase(cpu, gRenderer, 1, 1);
				cout << "p2 wins\n";
				return false;
			}

			if (quitGame == QUIT_GAME)	return true;
			//Transition scene add here
			cout << endl << "Change Turn" << endl;
		}

	}
	return false;
}

int Game::transitionPhase(int cpu, SDL_Renderer* &gRenderer, int win, int phase) {
	int quitGame = CONTINUE_TURN;
	SDL_Event e;
	int quoteNum = turn + cpu * 2 + win * 4 - 1;
	if (!gPhaseText.loadFromRenderedText(phaseQuote[phase], mColorWhite, gRenderer, gFont)) {
		printf("Failed to load phase text\n");
		return QUIT_GAME;
	}
	if (!gTransitionText.loadFromRenderedText(transitionQuote[quoteNum], mColorWhite, gRenderer, gFont)) {
		printf("Failed to load transition text\n");
		return QUIT_GAME;
	}
	while (quitGame == CONTINUE_TURN)
	{

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//X out of game
			if (e.type == SDL_QUIT) {
				quitGame = QUIT_GAME;
				break;
			}
			else if (gChoice[DONE].handleEvent(&e)) {
				quitGame = END_TURN;
			}
			
		}
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		if (turn == 1)
			gBackgroundP1.render(0, 0, gRenderer, full_screen);
		else
			gBackgroundP2.render(0, 0, gRenderer, full_screen);
		//Render transition quote
		gTransitionText.render(300, 300, gRenderer, transition_space[win]);
		if (win == 0) {
			gPhaseText.render(100, 100, gRenderer, phase_space);
		}
		//Render choice
		{
			gChoice[DONE].render(gChoiceSpriteSheetTexture, gRenderer);
			gText[DONE].render(641, 442, gRenderer, choice_button);
		}
		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	return quitGame;
}

int Game::deployPhase(sG &p, int cpu, SDL_Renderer* &gRenderer) {
	if (cpu) {
		for (int i = 1;i <= BOARD_SIDE;++i) {
			bool placeCorrect;
			int dir, x, y;
			do {
				placeCorrect = false;
				dir = rand() % 4;
				x = rand() % 10 + 1, y = rand() % 10 + 1;
				placeCorrect = p.checkShipPosition(x, y, dir, i);
			} while (!placeCorrect);
			p.createShip(x, y, dir, i);
		}
		return END_TURN;
	}
	else {
		int quitGame = CONTINUE_TURN;
		int shipCount = 1;

		//initial set up
		int dir = UNDEFINED, x = 0, y = 0;

		SDL_Event e;

		while (!quitGame)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//X out of game
				if (e.type == SDL_QUIT)
				{
					quitGame = QUIT_GAME;
				}
				else if (shipCount <= SHIP_NUMBER) {
					//choose position for ship head
					for (int i = 1; i <= BOARD_SIDE; ++i) {
						for (int j = 1;j <= BOARD_SIDE; ++j) {
							if (p.currentState(j, i) == SHIP_NONE && x == 0 && y == 0) {
								if (gButtons[i][j].handleEvent(&e)) {
									//Sth happens here
									x = j;
									y = i;
									//Create ship asap when ship length is only 1 (skip direction choice)
									if (shipCount >= 7) {
										p.createShip(x, y, 0, shipCount);
										shipCount++;
										//reset
										x = 0;
										y = 0;
										dir = UNDEFINED;
									}
									//Create ship nose with dir = 5 (undefined)
									else {
										p.createShip(x, y, dir, shipCount);
									}
								}
							}
						}
					}
					/*
					if (x == 0 && y == 0) {
						if (shipCount > 1) {
							if (gChoice[UNDO].handleEvent(&e)) {
								//p.undoShip(shipCount);
								//shipCount--;
							}
						}
					}
					*/
					//choose direction for ship
					if (x != 0 && y != 0) {
						for (int i = 0;i < TOTAL_ARROWS;++i) {
							if (gArrow[i].handleEvent(&e)) {
								dir = i;
								cout << dir << endl;
								if (p.checkShipPosition(x, y, dir, shipCount)) {
									p.createShip(x, y, dir, shipCount);
									shipCount++;
								}
								else {
									//add cant place here
									cout << "CANT PLACE" << endl;
								}
								//reset
								x = 0;
								y = 0;
								dir = UNDEFINED;
							}
						}
					}
				}
				else if (shipCount > SHIP_NUMBER) {
					if (gChoice[DONE].handleEvent(&e)) {
						SDL_Delay(1000);
						return END_TURN;
					}
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Render background
			if (turn == 1)
				gBackgroundP1.render(0, 0, gRenderer, full_screen);
			else
				gBackgroundP2.render(0, 0, gRenderer, full_screen);
			//Render buttons
			for (int i = 1; i <= BOARD_SIDE; ++i) {
				for (int j = 1;j <= BOARD_SIDE;++j) {
					gButtons[i][j].render(gButtonSpriteSheetTexture, gRenderer);
				}
			}
			//Render direction buttons
			for (int i = 0;i < TOTAL_ARROWS;++i) {
				gArrow[i].render(gArrowSpriteSheetTexture, gRenderer, ARROW_ANGLE[i]);
			}
			//Render choice buttons
			/*
			if (shipCount > 1) {
				gChoice[UNDO].render(gChoiceSpriteSheetTexture, gRenderer);
				gText[UNDO].render(641, 342, gRenderer, choice_button);
			}
			*/
			if (shipCount > SHIP_NUMBER) {
				gChoice[DONE].render(gChoiceSpriteSheetTexture, gRenderer);
				gText[DONE].render(641, 442, gRenderer, choice_button);
			}
			//Render current grid
			for (int i = 1;i <= BOARD_SIDE;++i) {
				for (int j = 1;j <= BOARD_SIDE;++j) {
					gGridSpriteSheetTexture.render(GRID_WIDTH[i][j], GRID_HEIGHT[i][j], gRenderer, gSpriteClips[p.currentState(j,i)]);
				}
			}
			//Update screen
			SDL_RenderPresent(gRenderer);
		}
		return quitGame;
	}
}

int Game::battlePhase(sG &p, int cpu, SDL_Renderer* &gRenderer) {
	int quitGame = CONTINUE_TURN;
	int x = 0, y = 0;
	if (!gText[DONE].loadFromRenderedText("FIRE!", mColor, gRenderer, gFont)) {
		printf("Failed to load DONE text!\n");
		return false;
	}
	SDL_Event e;

	while (quitGame == CONTINUE_TURN)
	{
		
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0){
			//X out of game
			if (e.type == SDL_QUIT){
				quitGame = QUIT_GAME;
				break;
			}
			if (cpu) {
				do {
					x = rand() % BOARD_SIDE + 1;
					y = rand() % BOARD_SIDE + 1;
					cout << x << " " << y << endl;
				} while (p.currentState(x, y) >= SHIP_HIT);
				SDL_Delay(800);
				if (!p.fireHit(x, y)) {
					quitGame = END_TURN;
					break;
				}
				else if (!p.continueGame()) {
					quitGame = END_TURN;
					break;
				}
			}
			else for (int i = 1; i <= BOARD_SIDE; ++i) {
				for (int j = 1;j <= BOARD_SIDE; ++j) {
					if (p.currentState(j, i) < SHIP_HIT) {
						if ((x == 0 && y == 0) || ((x != 0 && y != 0) && (i != x || j != y))) {
							if (gButtons[i][j].handleEvent(&e)) {
								//Sth happens here
								x = i;
								y = j;

							}
						}
					}
				}
			}
			if (!cpu && x != 0 && y != 0) {
				if (gChoice[DONE].handleEvent(&e)) {
					SDL_Delay(300);
					if (!p.fireHit(y, x)) {
						quitGame = END_TURN;
					}
					else if (!p.continueGame()) {
						quitGame = END_TURN;
					}
					x = 0;
					y = 0;
				}
			}
		}
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		if (turn == 1)
			gBackgroundP1.render(0, 0, gRenderer, full_screen);
		else
			gBackgroundP2.render(0, 0, gRenderer, full_screen);

		//Render buttons
		
		for (int i = 1; i <= BOARD_SIDE; ++i) {
			for (int j = 1;j <= BOARD_SIDE; ++j) {
				gButtons[i][j].render(gButtonSpriteSheetTexture, gRenderer);
			}
		}
		

		for (int i = 1;i <= BOARD_SIDE;++i) {
			for (int j = 1;j <= BOARD_SIDE;++j) {
				//normal mode
				//int battleState = (p.currentState(j,i) <= 2) ? 0 : p.currentState(j, i);
				//god mode (debug for now)
				int battleState = p.currentState(j, i);
				gGridSpriteSheetTexture.render(GRID_WIDTH[i][j], GRID_HEIGHT[i][j], gRenderer, gSpriteClips[battleState]);
			}
		}
		//Render choice
		if (!cpu && x != 0 && y != 0) {
			gChoice[DONE].render(gChoiceSpriteSheetTexture, gRenderer);
			gText[DONE].render(641, 442, gRenderer, choice_button);
		}
		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	return quitGame;
	/*
	int x, y;
	if (!cpu) {
		cout << "x: ";
		cin >> x;
		cout << "y: ";
		cin >> y;			
	}
	else {
		//cpu code here
		x = rand() % 10 + 1;
		y = rand() % 10 + 1;
	}
	return p.fireHit(x, y);
	*/
}