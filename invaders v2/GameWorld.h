#pragma once

#include <cmath>
#include <D3D11.h>
#include <list>

#include "EntityListInstancer.h"
#include "EnemyGrid.h"
#include "Level.h"
#include "DrawableShooter.h"
#include "Wall.h"
#include "Camera.h"
#include "IWorld.h"

using namespace std;

#define WALL_COUNT 4

class GameWorld : public IWorld
{
	list<InstanceEntity> playerBullets;
	unique_ptr<EntityListInstancer> playerBulletGraphics;
	shared_ptr<DrawableShooter> player;
	shared_ptr<EnemyGrid> enemies;
	bool enemiesMovingRight;
	vector<shared_ptr<Wall>> walls;

	float enemyGridSpeed;
	float bulletSpeed;

	int lives;
	D3DXVECTOR3 playerStart;
public:
	GameWorld();
	~GameWorld();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	void CollideBullets();
	shared_ptr<DrawableShooter> GetPlayer(){return player;}

	shared_ptr<EnemyGrid> GetEnemies(){return enemies;}

	const list<InstanceEntity> &GetBullets(){return playerBullets;}

	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);

	static const int FIELD_WIDTH = 50;
	static const int FIELD_HEIGHT = 30;
};