#include "Menu.h"

using namespace std;





//main menu ui
void Menu::displayMenu() {
	cout << "enter 1 to play with cpu" << endl << "enter 2 to play in 2-player mode" << endl << "any number to exit" << endl;
	int n, cpu;
	cin >> n;
	Game *G;
	G = new Game();
	if (n == 1 || n == 2) {
		if (n == 1)	cpu = 1;
		else cpu = 0;
		G->preDeploy(cpu);
		delete G;
		displayMenu();
	}
}

Menu::Menu()
{
}


Menu::~Menu()
{
}
