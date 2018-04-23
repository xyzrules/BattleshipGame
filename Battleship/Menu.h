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
	//3 buttons choice
	BUTTON_CHOICE mCurrentButtonChoice;
	//Button texture
	LButton mButtons[3];
	//Sprite sheet used as button clips
	LTexture mButtonSpriteSheetTexture;
	//Background texture
	LTexture mMenuBackground;
public:
	Menu();
	~Menu();
	//Free memories in menu
	void free();
	//Load media files in menu
	bool loadMedia(SDL_Renderer* &gRenderer);
	//Show menu
	void displayMenu(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
};

