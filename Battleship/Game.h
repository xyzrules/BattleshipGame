#pragma once
#include "stdafx.h"
#include "ShipGrid.h"
#include "Button.h"

const int BOARD_SIDE = 10;
const int SHIP_NUMBER = 10;
const int BUTTON_SIZE = 50;
const int ARROW_SIZE = 50;
const double ARROW_ANGLE[4] = { 0.0, 90.0, 180.0, 270.0 };
const string transitionQuote[8] = { "Change control to Player 1", "Change control to Player 2", "Your Turn To Play", "CPU's Turn To Play", "P1 WINS", "P2 WINS", "YOU WIN", "YOU LOSE" };
const string phaseQuote[2] = { "DEPLOY PHASE" , "BATTLE PHASE" };

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

enum choice {
	UNDO = 0,
	DONE = 1,
	TOTAL_CHOICE = 2
};

class Game
{
	int turn;
	//grid
	LButton gButtons[BOARD_SIDE + 1][BOARD_SIDE + 1];
	LTexture gButtonSpriteSheetTexture;
	//arrows
	LButton gArrow[TOTAL_ARROWS];
	LTexture gArrowSpriteSheetTexture;
	//undo and done button
	LTexture gChoiceSpriteSheetTexture;
	LButton gChoice[TOTAL_CHOICE];
	//text & buttons
	TTF_Font* gFont;
	SDL_Color mColor = { 0, 0, 0 };
	LTexture gText[TOTAL_CHOICE];
	SDL_Rect choice_button = { 0, 0, 120, 60 };
	//transition text
	LTexture gTransitionText;
	SDL_Rect transition_space[2] = { { 0, 0, 400, 60 }, {0, 0, 300, 60} };
	LTexture gPhaseText;
	SDL_Rect phase_space = { 0, 0, 300, 60 };
	SDL_Color mColorWhite = { 255, 255, 255 };
	//background
	LTexture gBackgroundP1;
	LTexture gBackgroundP2;
	SDL_Rect full_screen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
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
	//Transition phase
	int transitionPhase(int cpu, SDL_Renderer* &gRenderer, int win, int phase);
	//Deploy phase loop
	int deployPhase(sG &p, int cpu, SDL_Renderer* &gRenderer);
	//Battle phase loop
	int battlePhase(sG &p, int cpu, SDL_Renderer* &gRenderer);
};
