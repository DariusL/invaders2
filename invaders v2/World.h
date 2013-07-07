#pragma once
#include "Player.h"
#include "Globals.h"
#include "EnemyGrid.h"
#include "Logger.h"
#include "sstream"
#include <cmath>
#include <D3D11.h>

class World
{
	Player player;
	EnemyGrid enemies;
	bool enemiesMovingRight;
	int frameRate;
public:
	World();

	bool Init(unsigned int fRate);

	void OnLoop(int input);
	D3DXVECTOR3 GetPlayerPos(){return player.getPos();}

	EnemyGrid *GetEnemies(){return &enemies;}

	//borders
	static const int FIELD_WIDTH = 50;
	static const int FIELD_HEIGHT = 30;
};