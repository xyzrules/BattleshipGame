#include "Game.h"

Game::Game() {
	cout << "START GAME" << endl;
}

void Game::mainGame(int cpu) {
	sG P2, P1;
	cout << "P1 deploy phase" << endl;
	deployPhase(P1, cpu);
	if (cpu)	cout << "CPU deploy phase" << endl;
	else	cout << "P2 deploy phase" << endl;
	deployPhase(P2, cpu);
	battlePhase(P1, P2, cpu);
}

void Game::deployPhase(sG &p, int cpu) {
	if (cpu) srand(time(0));
	for (int i = 1;i <= 10;++i) {
		bool placeCorrect;
		cout << "Ship number " << i << endl;
		do {
			placeCorrect = false;
			//dir : 0 = horizontal; 1 = vertical
			int dir, x, y;
			if (cpu) {
				dir = rand() % 2;
				x = rand() % 10 + 1, y = rand() % 10 + 1;
			}
			else {
				
				cout << "Choose your pos from (1 1) to (10 10): ";
				cin >> x >> y;
				cout << "Choose your direction (0 for horizontal, 1 for vertical): ";
				cin >> dir;
			}
			placeCorrect = p.checkShipPosition(x, y, dir, i);
		} while (!placeCorrect);
	}
}

void Game::battlePhase(sG &p1 ,sG &p2, int cpu) {
	while (true) {
		while (fireAt(p2, 1)) {
			cout << endl << endl << " " << p2.continueGame() << endl;
			if (!p2.continueGame()){
				cout << "p1 wins\n";
				gameOver = true;
				break;
			}
		}
		cout << endl << endl << " " << p2.continueGame() << endl;
		if (gameOver)	break;
		cout << endl << "Change Turn" << endl;
		while (fireAt(p1, cpu)) {
			cout << endl << endl << " " << p1.continueGame() << endl;
			if (!p1.continueGame()) {
				cout << "p2 wins\n";
				gameOver = true;
				break;
			}
		}
		cout << endl << endl << " " << p1.continueGame() << endl;
		if (gameOver)	break;
		cout << endl << "Change Turn" << endl;
	}
}

bool Game::fireAt(sG &p, int cpu) {
	int x, y;
	if (!cpu) {
		cout << "x: ";
		cin >> x;
		cout << "y: ";
		cin >> y;			
	}
	else {
		//cpu code here
		x = rand() % 10 + 1;
		y = rand() % 10 + 1;
	}
	return p.fireHit(x, y);
}

Game::~Game() {
	cout << "END GAME" << endl;
}