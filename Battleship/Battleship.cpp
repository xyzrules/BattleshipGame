#include "stdafx.h"
#define first ft
#define second sd
#define push_back pb

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int oo = 1e8;

#define struct shipGrid sG

bool vsAI = 0, vsP2 = 0;

void play2Player();

void playWithAI();

void mainMenu() {
	cout << "enter 1 to play with ai" << endl << "enter 2 to play in 2-player mode" << endl << "any number to exit" << endl;
	int n;
	cin >> n;
	if (n == 1) {
		vsAI = 1;
		playWithAI();
		vsAI = 0;
	}
	else if (n == 2) {
		vsP2 = 1;
		play2Player();
		vsP2 = 0;
	}
}

void play2Player() {
	sG player1
}

void battleField() {

}

void deployPhasePlayer(sG player) {

}

void deployPhaseAI(sG player) {

}

void attackPhase(sG player) {

}

//update field after each fire attempt
void updateField(sG &);

//struct for player's grid field
struct shipGrid {
	int s[12][12] = { 0 };
	//s = abb;
	//a : 0 = none; 1 = banned position; 2 = ship; 3 = missed; 4 = ship hit; 5 = ship destroyed; 6 = banned position revealed;
	//bb: ship number 01 -> 10
	int shipCount = 10;
};

//
bool fire(int posx, int posy, sG &op) {
	int x = posx, y = posy;
	int a = s[x][y] / 100, bb = s[x][y] % 100;
	bool hit = true;
	if (a < 2) {
		op.s[x][y] = 3 * 100 + bb;
		hit = false;
	}
	else if (a == 2) {
		op.s[x][y] = 4 * 100 + bb;
	}
	updateField(&op);
	return hit;
}

void AI() {

}

void updateField(sG &op) {
	for (int i = 1;i <= 10;++i) {
		for (int j = 1;j <= 10;++j) {
			int a = s[x][y] / 100, bb = s[x][y] % 100;
			if (a==)
		}
	}
}


void mainGame() {
	sG p1, p2;
	bool gameOver = false;
	if (vsAI) {

	}
	else if (vsP2) {

	}
	while (!gameOver) {

	}
}

/*
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

bool init()
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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurface = loadSurface("_Playfield/grid10by10withbg506099.png");
	if (gPNGSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}
*/
int main(int argc, char* args[])
{
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