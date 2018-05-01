#include "stdafx.h"
#include "Game.h"
#include "ShipGrid.h"
#include "Menu.h"

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int oo = 1e8;

//Starts up SDL and creates window
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont);

//Frees media and shuts down SDL
void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont);

bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Battleship", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
				else {
					//Open the font 
					gFont = TTF_OpenFont("_Menu/global_font.ttf", 28);
					if (gFont == NULL) {
						printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
						success = false;
					}
				}
			}
		}
	}

	return success;
}

void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont)
{
	//Free global font 
	TTF_CloseFont(gFont); 
	gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* args[])
{
	Menu* menu = NULL;

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* gFont = NULL;

	srand(time(0));

	//Start up SDL and create window
	if (!init(gWindow, gRenderer, gFont))
	{
		printf("Failed to initialize!\n");
	}

	else
	{
		menu = new Menu();
		menu->displayMenu(gWindow, gRenderer, gFont);
		delete menu;
	}

	//Free resources and close SDL
	close(gWindow, gRenderer, gFont);
	
	_getch();
	return 0;
}
