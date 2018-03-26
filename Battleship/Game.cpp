#include "Game.h"

Game::Game() {
	cout << "START GAME" << endl;
}

void Game::preDeploy(int cpu) {
	sG P2, P1;
	cout << "P1 deploy phase" << endl;
	deployPhase(P1, cpu);
	if (cpu)	cout << "CPU deploy phase" << endl;
	else	cout << "P2 deploy phase" << endl;
	deployPhase(P2, cpu);
	playGame(P1, P2, cpu);
}

void Game::deployPhase(sG &p, int cpu) {
	if (cpu) srand(time(0));
	for (int i = 1;i <= 10;++i) {
		bool placeCorrect = false;
		do {
			//dir : 0 = horizontal; 1 = vertical
			int n, dir, x, y;
			if (cpu) {
				n = rand() % 100, dir = rand() % 2;
				x = n % 10 + 1, y = n / 10 + 1;
			}
			else {
				cout << "Ship number " << i << endl;
				cout << "Choose your pos from (1 1) to (10 10): ";
				cin >> x >> y;
				cout << "Choose your direction (0 for horizontal, 1 for vertical): ";
				cin >> dir;
			}
			placeCorrect = p.checkShipPosition(x, y, dir, i);
		} while (!placeCorrect);
	}
}

void Game::playGame(sG &p1 ,sG &p2, int cpu) {
	while (!gameOver) {
		fireAt(p2, cpu);
		if (!gameOver) {
			cout << "Change turn" << endl;
			fireAt(p1, cpu);
		}
		if (!gameOver) {
			cout << "Change turn" << endl;
		}
	}
}

void Game::fireAt(sG &p, int cpu) {
	bool turnOver = false;
	while (!turnOver) {
		int x, y;
		if (!cpu) {
			cout << "x: ";
			cin >> x;
			cout << "y: ";
			cin >> y;			
		}
		else {
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
		}
		if (!p.fireHit(x, y))
			turnOver = true;
		if (!p.continueGame()) {
			gameOver = true;
			turnOver = true;
		}
		cout << "turn over" << turnOver << endl;
	}
}

Game::~Game() {
	cout << "END GAME" << endl;
}