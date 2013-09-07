#pragma once
#pragma warning(disable : 4005)

#include <cmath>
#include <D3D11.h>
#include <list>

#include "EntityListInstancer.h"
#include "EnemyGrid.h"
#include "Level.h"
#include "DrawableShooter.h"
#include "Wall.h"

using namespace std;

class World : public IDrawable
{
	list<InstanceEntity> playerBullets;
	unique_ptr<EntityListInstancer> playerBulletGraphics;
	shared_ptr<DrawableShooter> player;
	shared_ptr<EnemyGrid> enemies;
	bool enemiesMovingRight;
	shared_ptr<Wall> tempWall;

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
	shared_ptr<DrawableShooter> GetPlayer(){return player;}

	shared_ptr<EnemyGrid> GetEnemies(){return enemies;}

	const list<InstanceEntity> &GetBullets(){return playerBullets;}

	bool IsStarted(){return started;}

	bool Init(ComPtr<ID3D11Device>);
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