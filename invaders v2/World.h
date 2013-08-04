#pragma once
#include "Shooter.h"
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
	Shooter player;
	EnemyGrid enemies;
	bool enemiesMovingRight;

	float enemyGridSpeed;
	float bulletSpeed;

	int lives;
	D3DXVECTOR3 playerStart;
public:
	World();
	~World();

	bool Init();

	void OnLoop(int input, float frameLength);
	void CollideBullets();
	Shooter &GetPlayer(){return player;}

	EnemyGrid *GetEnemies(){return &enemies;}

	const list<Entity> &GetBullets(){return playerBullets;}

	static const int FIELD_WIDTH = 50;
	static const int FIELD_HEIGHT = 30;
};