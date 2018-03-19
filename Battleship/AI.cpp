#include "stdafx.h"
#include "ShipGrid.h"

using namespace std;

void deployPhaseAI(sG &AI) {
	srand(time(0));
	for (int i = 1;i <= 10;++i) {
		bool placeCorrect = false;
		do {
			//dir : 0 = horizontal; 1 = vertical
			int n = rand() % 100, dir = rand() % 2;
			int x = n % 10, y = n / 10;
			placeCorrect = AI.checkShipPosition(x, y, dir, i);
		} while (!placeCorrect);
	}
}

void playWithAI() {
	sG AI;
	deployPhaseAI(AI);

}