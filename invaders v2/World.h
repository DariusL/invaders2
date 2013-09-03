#pragma once
#include "Shooter.h"
#include "Globals.h"
#include "EnemyGrid.h"
#include "Logger.h"
#include "Bullets.h"
#include <cmath>
#include <D3D11.h>
#include <list>

using namespace std;

class World : public IDrawable
{
	list<Entity> playerBullets;
	unique_ptr<Bullets> playerBulletGraphics;
	shared_ptr<Shooter> player;
	shared_ptr<EnemyGrid> enemies;
	bool enemiesMovingRight;

	float enemyGridSpeed;
	float bulletSpeed;

	int lives;
	D3DXVECTOR3 playerStart;
	bool started;
public:
	World();
	~World();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	void CollideBullets();
	shared_ptr<Shooter> GetPlayer(){return player;}

	shared_ptr<EnemyGrid> GetEnemies(){return enemies;}

	const list<Entity> &GetBullets(){return playerBullets;}

	bool IsStarted(){return started;}

	bool Init(ID3D11Device*, HWND);
	void Render(RenderParams);

	static const int FIELD_WIDTH = 50;
	static const int FIELD_HEIGHT = 30;

	enum Result
	{
		CONTINUE,
		GAME_OVER,
		NEXT_LEVEL
	};
};