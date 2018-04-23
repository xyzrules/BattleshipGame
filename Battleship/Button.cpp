#include "Button.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	BUTTON_HEIGHT = 0;
	BUTTON_WIDTH = 0;
}


void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::setSize_Sprites( int x, int y) {
	BUTTON_WIDTH = x;
	BUTTON_HEIGHT = y;

	for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
	{
		gSpriteClips[i].x = 0;
		gSpriteClips[i].y = i * BUTTON_HEIGHT;
		gSpriteClips[i].w = BUTTON_WIDTH;
		gSpriteClips[i].h = BUTTON_HEIGHT;
	}
}

bool LButton::handleEvent( SDL_Event* e)
{
	bool success = false;
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){

		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		if( x < mPosition.x ||  x > mPosition.x + BUTTON_WIDTH || y > mPosition.y + BUTTON_HEIGHT || y < mPosition.y ){
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		} 
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;
				
				case SDL_MOUSEBUTTONUP: 
				if (mCurrentSprite == BUTTON_SPRITE_MOUSE_DOWN)	success = true;
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
	if (success)	cout << mPosition.x << " " << mPosition.y << " " << endl;
	return success;
}
	
void LButton::render(LTexture &gButtonSpriteSheetTexture, SDL_Renderer* &gRenderer, double angle)
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, gRenderer, gSpriteClips[ mCurrentSprite ], angle);
}
