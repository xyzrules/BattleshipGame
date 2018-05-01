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
	TOTAL_ARROWS = 4,
	UNDEFINED = 5
};

enum gameCondition {
	CONTINUE_TURN = 0,
	END_TURN = 1,
	QUIT_GAME = 2
};

//s = abb;
//a : 0 = none; 1 = banned position; 2 = ship; 3 = missed; 4 = ship hit; 5 = ship destroyed; 6 = banned position revealed, 7 = ship head;
//bb: ship number 01 -> 10

enum gridSprite {
	SHIP_NONE = 0,
	BANNED_POS = 1,
	SHIP = 2,
	MISSED = 3,
	SHIP_HIT = 4,
	SHIP_DESTROYED = 5,
	BANNED_POS_REVEALED = 6,
	SHIP_NOSE = 7,
	GRID_TOTAL_SPRITE = 8
};

class Game
{
	LButton gButtons[BOARD_SIDE + 1][BOARD_SIDE + 1];
	LButton gArrow[TOTAL_ARROWS];
	LTexture gButtonSpriteSheetTexture;
	LTexture gArrowSpriteSheetTexture;
	LTexture gBackground;
	LTexture gChoice[3];
	//grid
	LTexture gGridSpriteSheetTexture;
	SDL_Rect gSpriteClips[GRID_TOTAL_SPRITE];
	int GRID_WIDTH[BOARD_SIDE + 1][BOARD_SIDE + 1], GRID_HEIGHT[BOARD_SIDE + 1][BOARD_SIDE + 1];
	//battle phase use only
	gridSprite gridCurrentSprite[BOARD_SIDE + 1][BOARD_SIDE + 1];

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
