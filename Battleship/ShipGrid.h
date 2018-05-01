#pragma once
#include "stdafx.h"

using namespace std;


//class for each player ship grid
class sG
{
	//ship grid
	int s[13][13] = { 0 };
	//ship count by total length
	int shipCount = 20;
	//cpu (bot) uses only
	int cpuDir;
	//length for each ship (from 1 -> 10, 0 does nothing)
	int shipLength[11] = { 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0 };
	//direction
	int surroundX[8] = { -1,0,1,0,-1,-1,1,1 };
	int surroundY[8] = { 0,1,0,-1,1,-1,-1,1 };
	
	//functions for cpu (bot) uses only
	friend void setCpuDir(sG cpu, int dir);
	friend int getCpuDir(sG cpu);

public:

	//return current state of 1 specific grid (ship appeared or banned position, etc.)
	//0 = none; 1 = banned position; 2 = ship; 3 = missed; 4 = ship hit; 5 = ship destroyed; 6 = banned position revealed, 7 = ship head;
	int currentState(int x, int y);

	//return if ship pos is out of bounds
	bool checkOutOfBounds(int x, int y);

	//return if ship is able to place or not (eg. banned position or out of bounds)
	bool checkShipPosition(int x, int y, int dir, int shipNumber);

	//create ship with position and direction intended
	void createShip(int x, int y, int dir, int shipNumber);

	//quick update after each fire attempt
	void updateField();

	//show field
	void revealField();

	//player hits or misses ship
	bool fireHit(int x, int y);

	//end game condition
	bool continueGame();

};