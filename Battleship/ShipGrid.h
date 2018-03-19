#pragma once
#include "stdafx.h"

class shipGrid
{
	int s[12][12] = { 0 };
	//s = abb;
	//a : 0 = none; 1 = banned position; 2 = ship; 3 = missed; 4 = ship hit; 5 = ship destroyed; 6 = banned position revealed;
	//bb: ship number 01 -> 10
	int shipCount = 10;

	int shipLength[11] = { 5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	int surroundX[8] = { 1,0,-1,-1,-1,0,1,1 };
	int surroundY[8] = { 0,1,-1,0,1,-1,-1,1 };
public:
	//return if ship is able to place or not (eg. banned position or out of bounds)
	//create ship during the check
	bool checkShipPosition(int x, int y, int dir, int shipNumber);

	//player hits or misses ship
	bool fire(int x, int y);

	//quick update after each fire attempt
	void updateField();
};