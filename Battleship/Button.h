#include "stdafx.h"
#include "Texture.h"

#pragma once

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

class LButton {
public: 
	//Initializes internal variables 
	LButton(); 
	//Sets top left position 
	void setPosition( int x, int y ); 
	//Handles mouse event 
	bool handleEvent( SDL_Event* e); 
	//Sets button size and sprites
	void setSize_Sprites(int WIDTH, int HEIGHT);
	//Shows button sprites
	void render(LTexture &gButtonSpriteSheetTexture, SDL_Renderer* &gRenderer);
	
private:
	SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
	//Top left position 
	SDL_Point mPosition; 
	//Currently used global sprite 
	LButtonSprite mCurrentSprite; 
	//Button width and height
	int BUTTON_WIDTH, BUTTON_HEIGHT;
};
