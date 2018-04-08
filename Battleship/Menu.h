#pragma once
#include "stdafx.h"
#include "Game.h"
#include "Button.h"
#include "Text.h"

enum BUTTON_CHOICE {
	PLAYER_VS_MODE = 0,
	PLAYER_VS_CPU = 1,
	PLAYER_QUIT = 2,
	TOTAL_BUTTONS = 3
};

class Menu
{
	BUTTON_CHOICE mCurrentButtonChoice;
	LButton gButtons[3];
	LTexture gButtonSpriteSheetTexture;
public:
	void displayMenu(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
	Menu();
	~Menu();
};

