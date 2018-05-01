#include "Menu.h"

using namespace std;

Menu::Menu()
{
	cout << "START GAME" << endl;
}


Menu::~Menu()
{
	free();
}

//Free texture memories
void Menu::free() {
	TTF_CloseFont(mFont);
	mFont = NULL;
	mButtonSpriteSheetTexture.free();
	mMenuBackground.free();
	for (int i = 0;i < TOTAL_BUTTONS;++i) {
		mText[i].free();
	}
}

bool Menu::loadMedia(SDL_Renderer* &gRenderer) {
	//Load sprite sheet
	if (!mButtonSpriteSheetTexture.loadFromFile("_Menu/start_button.png", gRenderer))
	{
		printf("Failed to load button sprite texture!\n");
		return false;
	}
	//Load background
	else if (!mMenuBackground.loadFromFile("_Menu/battleship_background.png", gRenderer)) {
		printf("Failed to load background image!\n");
		return false;
	}
	else {
		//Open the font 
		mFont = TTF_OpenFont("_Menu/Xenotron.ttf", 28);
		if (mFont == NULL) {
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			return false;
		}
	}
	//Set buttons size & sprites
	for (int i = 0;i < TOTAL_BUTTONS;++i) {
		mButtons[i].setSize_Sprites(300, 200);
	}

	//Set buttons in corners
	mButtons[PLAYER_VS_MODE].setPosition(500, 0);
	mButtons[PLAYER_VS_CPU].setPosition(500, 200);
	mButtons[PLAYER_QUIT].setPosition(500, 400);
	//Set ttf for buttons
	
	if (!mText[PLAYER_VS_MODE].loadFromRenderedText("P1 VS P2", mColor, gRenderer, mFont)) {
		printf("Failed to load player vs mode text!\n");
		return false;
	}
	else if (!mText[PLAYER_VS_CPU].loadFromRenderedText("P1 VS CPU", mColor, gRenderer, mFont)) {
		printf("Failed to load player vs cpu text!\n");
		return false;
	}
	else if (!mText[PLAYER_QUIT].loadFromRenderedText("QUIT GAME", mColor, gRenderer, mFont)) {
		printf("Failed to load player quit text!\n");
		return false;
	}
	
	return true;
}

void Menu::displayMenu(SDL_Window* &gWindow, SDL_Renderer* &gRenderer) {
	//Main loop flag
	bool quitMenu = false;

	//Event handler
	SDL_Event e;

	if (!loadMedia(gRenderer)) {
		printf("Load media failed\n");
	}
	else {
		//While application is running
		while (!quitMenu)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//X out of game
				if (e.type == SDL_QUIT)
				{
					quitMenu = true;
				}
				else {
					for (int i = 0; i < TOTAL_BUTTONS; ++i)
					{
						if (mButtons[i].handleEvent(&e)) {
							//User press quit button
							if (i == PLAYER_QUIT) {
								quitMenu = true;
							}
							else {
								Game *G;
								G = new Game();
								if (G->mainGame(i, gRenderer)) {
									quitMenu = true;
								}
								delete G;
								if (quitMenu)	break;
							}
						}
					}
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Render background
			mMenuBackground.render(0, 0, gRenderer, full_screen);

			//Render buttons
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				mButtons[i].render(mButtonSpriteSheetTexture, gRenderer);
			}
			//Render text
			mText[PLAYER_VS_MODE].render(543, 55, gRenderer, button);
			mText[PLAYER_VS_CPU].render(543, 255, gRenderer, button);
			mText[PLAYER_QUIT].render(543, 455, gRenderer, button);

			//Update screen
			SDL_RenderPresent(gRenderer);
		}
	}
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}