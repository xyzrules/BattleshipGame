#include "stdafx.h"
#include "ShipGrid.h"

using namespace std;

bool sG::fire(int posx, int posy) {
	int x = posx, y = posy;
	int a = s[x][y] / 100, bb = s[x][y] % 100;
	bool hit = true;
	if (a < 2) {
		s[x][y] = 3 * 100 + bb;
		hit = false;
	}
	else if (a == 2) {
		s[x][y] = 4 * 100 + bb;
		shipLength[bb]--;
	}
	updateField();
	return cout << "Result of fire :" << hit << endl, hit;
}

//s = abb;
//a : 0 = none; 1 = banned position; 2 = ship; 3 = missed; 4 = ship hit; 5 = ship destroyed; 6 = banned position revealed;
//bb: ship number 01 -> 10

void sG::updateField() {
	for (int i = 1;i <= 10;++i) {
		for (int j = 1;j <= 10;++j) {
			int a = s[i][j] / 100, bb = s[i][j] % 100;
			if (shipLength[bb] == 0) {
				a = 5;
				for (int k = 0;k <= 7;++k) {
					if (s[i + surroundX[k]][j + surroundY[k]] == 100) {
						s[i + surroundX[k]][j + surroundY[k]] = 600;
					}
				}
			}
			s[i][j] = a * 100 + bb;
		}
	}
}

bool sG::checkShipPosition(int x, int y, int dir, int shipNumber) {
	//dir : 0 = horizontal; 1 = vertical
	int lastX = x + surroundX[dir] * shipLength[shipNumber], lastY = y + surroundY[dir] * shipLength[shipNumber];
	if (lastX <= 10 || lastY <= 10) {
		if (!s[x][y] && !s[lastX][lastY]) {
			for (int i = x;i <= lastX;++i) {
				for (int j = y;j <= lastY;++j) {
					//create ship (2bb)
					s[i][j] == 200 + shipNumber;
					//ban position around the ship (100)
					for (int k = 0;k < 8;++k) {
						if (s[i + surroundX[k]][j + surroundY[k]] == 0) {
							s[i + surroundX[k]][j + surroundY[k]] = 100;
						}
					}
				}
			}
		}
		else return cout << "Ship failed to place: Banned position" << endl, false;
	}
	else return cout << "Ship failed to place: Out of bounds" << endl, false;

	return cout << "Create ship at " << x << " " << y << " " << dir << " with length: " << shipLength[shipNumber] << endl, true;
}