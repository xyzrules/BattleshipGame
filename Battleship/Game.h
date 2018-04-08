#pragma once
#include "stdafx.h"
#include "ShipGrid.h"

using namespace std;

class Game
{
	bool gameOver = 0;
public:
	Game();
	~Game();

	void battlePhase(sG &p1, sG &p2, int cpu);
	
	void mainGame(int cpu);
	
	void deployPhase(sG &p, int cpu);
	
	bool fireAt(sG &p, int cpu);
};
