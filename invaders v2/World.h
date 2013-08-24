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
	shared_ptr<Shooter> GetPlayer(){return player;}

	EnemyGrid *GetEnemies(){return &enemies;}

	const list<Entity> &GetBullets(){return playerBullets;}

	bool Init(ID3D11Device*, HWND);
	void Render(ID3D11DeviceContext*, D3DXMATRIX);

	static const int FIELD_WIDTH = 50;
	static const int FIELD_HEIGHT = 30;
};