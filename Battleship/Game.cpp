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
	gButtonSpriteSheetTexture.free();
	gArrowSpriteSheetTexture.free();
	gBackground.free();
}

bool Game::loadMedia(SDL_Renderer* &gRenderer) {
	//Load sprite sheet
	if (!gButtonSpriteSheetTexture.loadFromFile("_Playfield/button_outline.png", gRenderer))
	{
		printf("Failed to load button sprite texture!\n");
		return false;
	}
	//Load background
	else if (!gBackground.loadFromFile("_Menu/battleship_background.png", gRenderer)) {
		printf("Failed to load background image!\n");
		return false;
	}
	//Load direction sprite sheet
	else if (!gArrowSpriteSheetTexture.loadFromFile("_Playfield/arrow.png", gRenderer)){
		printf("Failed to load button sprite texture!\n");
		return false;
	}
	else {
		//Set buttons size, sprites & position
		for (int i = 0;i < BOARD_SIDE;++i) {
			for (int j = 0;j < BOARD_SIDE;++j) {
				gButtons[i+1][j+1].setSize_Sprites(50, 50);
				gButtons[i+1][j+1].setPosition(50 + 51 * i, 50 + 51 * j);
			}
		}
		for (int i = 0;i < TOTAL_ARROWS; ++i) {
			gArrow[i].setSize_Sprites(50, 50);
			if (i == UP_ARROW) gArrow[i].setPosition(675, 300);
			if (i == RIGHT_ARROW) gArrow[i].setPosition(725, 350);
			if (i == DOWN_ARROW) gArrow[i].setPosition(675, 400);
			if (i == LEFT_ARROW) gArrow[i].setPosition(625, 350);
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
		//Transition scene add here

		cout << "P1 deploy phase" << endl;
		if (deployPhase(P1, 0, gRenderer) == QUIT_GAME) {
			return true;
		}
		//Transition scene add here

		if (cpu)	cout << "CPU deploy phase" << endl;
		else	cout << "P2 deploy phase" << endl;
		if (deployPhase(P2, cpu, gRenderer) == QUIT_GAME) {
			return true;
		}
		//Transition scene add here

		while (true) {
			int quitGame = 2;

			//p1 turn
			while ((quitGame = battlePhase(P2, 0, gRenderer)) == CONTINUE_TURN) {
				cout << endl << endl << " " << P2.continueGame() << endl;
				if (!P2.continueGame()) {
					//Winning scene add here
					cout << "p1 wins\n";
					return false;
				}
			}
			if (quitGame == QUIT_GAME)	return true;
			//Transition scene add here
			cout << endl << "Change Turn" << endl;

			//p2 turn
			while ((quitGame = battlePhase(P1, 0, gRenderer)) == CONTINUE_TURN) {
				cout << endl << endl << " " << P1.continueGame() << endl;
				if (!P1.continueGame()) {
					//Winning scene add here
					cout << "p2 wins\n";
					return false;
				}
			}
			if (quitGame == QUIT_GAME)	return true;
			//Transition scene add here
			cout << endl << "Change Turn" << endl;
		}

	}
	return false;
}

int Game::deployPhase(sG &p, int cpu, SDL_Renderer* &gRenderer) {
	if (cpu) {
		srand(time(0));
		for (int i = 1;i <= BOARD_SIDE;++i) {
			bool placeCorrect;
			do {
				placeCorrect = false;
				//dir : 0 = horizontal; 1 = vertical
				int dir, x, y;
				dir = rand() % 2;
				x = rand() % 10 + 1, y = rand() % 10 + 1;
				placeCorrect = p.checkShipPosition(x, y, dir, i);
			} while (!placeCorrect);
		}
		return END_TURN;
	}
	else {
		int quitGame = CONTINUE_TURN;
		int shipCount = 1;

		//initial set up
		int dir = 4, x = 0, y = 0;

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
							if (p.emptyPosition(j, i)) {
								if (gButtons[i][j].handleEvent(&e)) {
									//Sth happens here
									x = j;
									y = i;
									cout << x << " " << y << endl;
								}
							}
						}
					}
					//choose direction for ship
					if (x != 0 && y != 0) {
						for (int i = 0;i < TOTAL_ARROWS;++i) {
							if (gArrow[i].handleEvent(&e)) {
								dir = i;
								cout << dir << endl;
								if (p.checkShipPosition(x, y, dir, shipCount)) {
									p.createShip(x, y, dir, shipCount);
									shipCount++;
									//reset
									x = 0;
									y = 0;
								}
								else {
									//add cant place here
									cout << "CANT PLACE" << endl;
								}
							}
						}
					}
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Render background
			SDL_Rect full_screen = { 0, 0, 800, 600 };
			gBackground.render(0, 0, gRenderer, full_screen);

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

			//Update screen
			SDL_RenderPresent(gRenderer);

			 
			if (shipCount > SHIP_NUMBER) {
				SDL_Delay(1000);
				return END_TURN;
			}
		}
		return quitGame;
	}
}


int Game::battlePhase(sG &p, int cpu, SDL_Renderer* &gRenderer) {
	int quitGame = CONTINUE_TURN;

	SDL_Event e;

	while (quitGame == CONTINUE_TURN)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//X out of game
			if (e.type == SDL_QUIT)
			{
				quitGame = QUIT_GAME;
				break;
			}
			for (int i = 1; i <= BOARD_SIDE; ++i) {
				for (int j = 1;j <= BOARD_SIDE; ++j) {
					if (cpu) {
						int x, y;
						x = rand() % BOARD_SIDE + 1;
						y = rand() % BOARD_SIDE + 1;
					}
					else if (gButtons[i][j].handleEvent(&e)) {
						//Sth happens here
						if (!p.fireHit(j, i)) {
							quitGame = END_TURN;
						}
					}
				}
			}	
		}
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render background
		SDL_Rect full_screen = { 0, 0, 800, 600 };
		gBackground.render(0, 0, gRenderer, full_screen);

		//Render buttons
		for (int i = 1; i <= BOARD_SIDE; ++i) {
			for (int j = 1;j <= BOARD_SIDE; ++j) {
				gButtons[i][j].render(gButtonSpriteSheetTexture, gRenderer);
			}
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