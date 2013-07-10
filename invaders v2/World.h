#pragma once
#include "Entity.h"
#include "Globals.h"
#include "EnemyGrid.h"
#include "Logger.h"
#include <cmath>
#include <D3D11.h>
#include <list>

using namespace std;

class World
{
	list<Entity> playerBullets;
	Entity player;
	EnemyGrid enemies;
	bool enemiesMovingRight;
	int frameRate;
public:
	World();
	~World();

	bool Init(unsigned int fRate);

	void OnLoop(int input);
	D3DXVECTOR3 GetPlayerPos(){return player.GetPos();}

	EnemyGrid *GetEnemies(){return &enemies;}

	const list<Entity> &GetBullets(){return playerBullets;}

	static const int FIELD_WIDTH = 50;
	static const int FIELD_HEIGHT = 30;
};