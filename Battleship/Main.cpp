#include "stdafx.h"
#include "Game.h"
#include "ShipGrid.h"
#include "Menu.h"

using namespace std;

int main(int argc, char* args[])
{
	Menu menu;
	menu.displayMenu();
	/*
	//Start up SDL and create window
	if (!init())
	{
	printf("Failed to initialize!\n");
	}
	else
	{
	//Load media
	if (!loadMedia())
	{
	printf("Failed to load media!\n");
	}
	else
	{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

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
	}

	//Apply the PNG image
	SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
	}
	}
	}

	//Free resources and close SDL
	close();
	*/
	_getch();
	return 0;
}
