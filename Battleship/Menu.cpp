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
		//Set buttons size & sprites
		for (int i = 0;i < TOTAL_BUTTONS;++i) {
			mButtons[i].setSize_Sprites(300, 200);
		}

		//Set buttons in corners
		mButtons[0].setPosition(500, 0);
		mButtons[1].setPosition(500, 200);
		mButtons[2].setPosition(500, 400);
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
								free();
								Game *G;
								G = new Game();
								if (G->mainGame(i, gRenderer)) {
									quitMenu = true;
								}
								delete G;
								if (quitMenu)	break;
								else if (!loadMedia(gRenderer)) {
									printf("Load media failed\n");
								}
							}
						}
					}
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Render background
			SDL_Rect full_screen = { 0, 0, 800, 600 };
			mMenuBackground.render(0, 0, gRenderer, full_screen);

			//Render buttons
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				mButtons[i].render(mButtonSpriteSheetTexture, gRenderer);
			}

			//Update screen
			SDL_RenderPresent(gRenderer);
		}
	}
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}