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
	void playGame(sG &p1, sG &p2, int cpu);
	void preDeploy(int cpu);
	void deployPhase(sG &p, int cpu);
	bool isGameOver();
	void fireAt(sG &p, int cpu);
};
