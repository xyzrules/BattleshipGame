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
	mButtonSpriteSheetTexture.free();
	mMenuBackground.free();
	for (int i = 0;i < TOTAL_BUTTONS;++i) {
		mText[i].free();
	}
}

bool Menu::loadMedia(SDL_Renderer* &gRenderer, TTF_Font* &gFont) {
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
		//Set buttons size & sprites
		for (int i = 0;i < TOTAL_BUTTONS;++i) {
			mButtons[i].setSize_Sprites(300, 200);
		}

		//Set buttons in corners
		mButtons[PLAYER_VS_MODE].setPosition(500, 0);
		mButtons[PLAYER_VS_CPU].setPosition(500, 200);
		mButtons[PLAYER_QUIT].setPosition(500, 400);
	}
	SDL_Color mColor = {0, 0, 0};
	if (!mText[PLAYER_VS_MODE].loadFromRenderedText("P1 VS P2", mColor, gRenderer, gFont)) {
		printf("Failed to load player vs mode text!\n");
		return false;
	}
	else if (!mText[PLAYER_VS_CPU].loadFromRenderedText("P1 VS CPU", mColor, gRenderer, gFont)) {
		printf("Failed to load player vs mode text!\n");
		return false;
	}
	else if (!mText[PLAYER_QUIT].loadFromRenderedText("QUIT GAME", mColor, gRenderer, gFont)) {
		printf("Failed to load player vs mode text!\n");
		return false;
	}
		
	
	return true;
}

void Menu::displayMenu(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont) {
	//Main loop flag
	bool quitMenu = false;

	//Event handler
	SDL_Event e;

	if (!loadMedia(gRenderer, gFont)) {
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
			mText[PLAYER_VS_MODE].render(560, 30, gRenderer, button);
			mText[PLAYER_VS_CPU].render(500, 200, gRenderer, button);
			mText[PLAYER_QUIT].render(500, 400, gRenderer, button);

			//Update screen
			SDL_RenderPresent(gRenderer);
		}
	}
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}