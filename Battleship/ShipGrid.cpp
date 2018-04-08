#include "ShipGrid.h"

using namespace std;

void setCpuDir(sG cpu, int dir) {
	cpu.cpuDir = dir;
}

int getCpuDir(sG cpu) {
	return cpu.cpuDir;
}

bool sG::fireHit(int posx, int posy) {
	int x = posx, y = posy;
	int a = s[x][y] / 100, bb = s[x][y] % 100;
	bool hit = false;
	if (a < 2) {
		s[x][y] = 3 * 100 + bb;
	}
	else if (a == 2) {
		hit = true;
		s[x][y] = 4 * 100 + bb;
		shipLength[bb]--;
		shipCount--;
	}
	updateField();
	revealField();
	return cout << "Result of fire: " << hit << endl, hit;
} 

//s = abb;
//a : 0 = none; 1 = banned position; 2 = ship; 3 = missed; 4 = ship hit; 5 = ship destroyed; 6 = banned position revealed;
//bb: ship number 01 -> 10

void sG::updateField() {
	for (int i = 1;i <= 10;++i) {
		for (int j = 1;j <= 10;++j) {
			int a = s[i][j] / 100, bb = s[i][j] % 100;
			if (shipLength[bb] == -1 && a != 5) {
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

void sG::revealField() {
	
	cout << endl;
	for (int i = 1;i <= 10;++i) {
		for (int j = 1;j <= 10;++j) {
			cout << s[i][j] / 100 << " ";
		}
		cout << endl;
	}
	cout << endl;
	
}

bool sG::checkOutOfBounds(int x, int y) {
	if (x >= 0 && y >= 0 && x <= 10 && y <= 10)	return true;
	else return false;
}

bool sG::checkShipPosition(int x, int y, int dir, int shipNumber) {
	//dir : 0 = horizontal; 1 = vertical
	int lastX = x + surroundX[dir] * shipLength[shipNumber], lastY = y + surroundY[dir] * shipLength[shipNumber];
	if (checkOutOfBounds(lastX, lastY)) {
		if (s[x][y] == 0 && s[lastX][lastY] == 0) {
			for (int i = x;i <= lastX;++i) {
				for (int j = y;j <= lastY;++j) {
					//create ship (2bb)
					s[i][j] = 200 + shipNumber;
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
	else {
		return cout << "Ship failed to place: Out of bounds" << endl, false;
	}
	revealField();
	return cout << "Create ship at " << x << " " << y << " " << dir << " with length: " << shipLength[shipNumber] << endl, true;
	
}

bool sG::continueGame() {
	return cout << shipCount << endl, (shipCount > 0);
}