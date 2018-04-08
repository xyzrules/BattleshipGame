#pragma once
#include "stdafx.h"

using namespace std;

class shipGrid
{
	int s[13][13] = { 0 };
	//s = abb;
	//a : 0 = none; 1 = banned position; 2 = ship; 3 = missed; 4 = ship hit; 5 = ship destroyed; 6 = banned position revealed;
	//bb: ship number 01 -> 10
	int shipCount = 20;

	int cpuDir;

	int shipLength[11] = { 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0 };
	int surroundX[8] = { 0,1,0,-1,-1,-1,1,1 };
	int surroundY[8] = { 1,0,-1,0,1,-1,-1,1 };

	friend void setCpuDir(sG cpu, int dir);
	friend int getCpuDir(sG cpu);

public:
	//return if ship is able to place or not (eg. banned position or out of bounds)
	//create ship during the check

	bool checkShipPosition(int x, int y, int dir, int shipNumber);

	//return if ship pos is out of bounds
	bool checkOutOfBounds(int x, int y);

	//player hits or misses ship
	bool fireHit(int x, int y);

	//quick update after each fire attempt
	void updateField();

	//show field
	void revealField();

	//end game condition
	bool continueGame();
};