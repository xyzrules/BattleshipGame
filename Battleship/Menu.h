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
	LButton mButtons[TOTAL_BUTTONS];
	//Sprite sheet used as button clips
	LTexture mButtonSpriteSheetTexture;
	//Background texture
	LTexture mMenuBackground;
	//Text texture
	LTexture mText[TOTAL_BUTTONS];
	SDL_Rect full_screen = { 0, 0, 800, 600 };
	SDL_Rect button = { 0 , 0 , 150, 120 };
public:
	Menu();
	~Menu();
	//Free memories in menu
	void free();
	//Load media files in menu
	bool loadMedia(SDL_Renderer* &gRenderer, TTF_Font* &gFont);
	//Show menu
	void displayMenu(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont);
};

