#include "Menu.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int oo = 1e8;

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

//main menu ui
void Menu::displayMenu() {
	cout << "enter 1 to play with cpu" << endl << "enter 2 to play in 2-player mode" << endl << "any number to exit" << endl;
	int n;
	cin >> n;
	Game *G;
	if (n == 1) {
		G = new Game();
		G->playWithCPU();
		delete G;
	}
	else if (n == 2) {
		G = new Game;
		G->playWithP2();
		delete G;
	}
	displayMenu();
}

Menu::Menu()
{
}


Menu::~Menu()
{
}
