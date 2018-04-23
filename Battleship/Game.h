#pragma once
#include "stdafx.h"
#include "ShipGrid.h"
#include "Button.h"

const int BOARD_SIDE = 10;
const int SHIP_NUMBER = 10;
const int BUTTON_SIZE = 50;
const int ARROW_SIZE = 50;
const double ARROW_ANGLE[4] = { 0.0, 90.0, 180.0, 270.0 };

enum gameArrow {
	UP_ARROW = 0,
	RIGHT_ARROW = 1,
	DOWN_ARROW = 2,
	LEFT_ARROW = 3,
	TOTAL_ARROWS = 4
};

enum gameCondition {
	CONTINUE_TURN = 0,
	END_TURN = 1,
	QUIT_GAME = 2
};

class Game
{
	LButton gButtons[11][11];
	LButton gArrow[4];
	LTexture gButtonSpriteSheetTexture;
	LTexture gArrowSpriteSheetTexture;
	LTexture gBackground;
	LTexture gChoice[3];
public:
	Game();
	~Game();

	void free();
	//Load media in game
	bool loadMedia(SDL_Renderer* &gRenderer);
	//Main game loop
	bool mainGame(int cpu, SDL_Renderer* &gRenderer);
	//Deploy phase loop
	int deployPhase(sG &p, int cpu, SDL_Renderer* &gRenderer);
	//Battle phase loop
	int battlePhase(sG &p, int cpu, SDL_Renderer* &gRenderer);
};
