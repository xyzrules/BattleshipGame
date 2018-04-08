#include "Menu.h"

using namespace std;

//main menu ui
void Menu::displayMenu(SDL_Window* &gWindow, SDL_Renderer* &gRenderer) {
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	if (!gButtonSpriteSheetTexture.loadFromFile("_Playfield/startbutton.png", gRenderer))
	{
		printf("Failed to load button sprite texture!\n");
	}
	else
	{
		cout << "LOAD COMPLETE" << endl;
		for (int i = 0;i < TOTAL_BUTTONS;++i) {
			gButtons[i].setSize_Sprites(300, 200);
		}

		//Set buttons in corners
		gButtons[0].setPosition(400, 0);
		gButtons[1].setPosition(400, 200);
		gButtons[2].setPosition(400, 400);
	}

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//User requests play game
			else {
				for (int i = 0; i < TOTAL_BUTTONS; ++i)
				{
					if (gButtons[i].handleEvent(&e)) {
						if (i == PLAYER_QUIT) {
							quit = true;
						}
						else {
							gButtonSpriteSheetTexture.free();
							Game *G;
							G = new Game();
							G->mainGame(i);
							delete G;
							if (!gButtonSpriteSheetTexture.loadFromFile("_Playfield/startbutton.png", gRenderer))
							{
								printf("Failed to load button sprite texture!\n");
							}
						}
					}
				}
				/*
				cout << "enter 1 to play with cpu" << endl << "enter 2 to play in 2-player mode" << endl << "any number to exit" << endl;
				int n, cpu;
				cin >> n;
				
				*/
			}
		}
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render buttons
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			gButtons[i].render(gButtonSpriteSheetTexture, gRenderer);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}

Menu::Menu()
{
	cout << "START GAME" << endl;
}


Menu::~Menu()
{
	gButtonSpriteSheetTexture.free();
}
