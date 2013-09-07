#pragma once
#pragma warning(disable : 4005)

#include <vector>
#include <memory>
#include <list>
#include <random>

#include "IDrawable.h"
#include "Bullets.h"
#include "Level.h"
#include "Globals.h"
#include "Shooter.h"
#include "InstanceEntity.h"

using namespace std;
class EnemyGrid : public IDrawable
{
	vector<shared_ptr<Shooter>> grid;
	list<Entity> bullets;
	unique_ptr<Bullets> enemyBulletGraphics;
	shared_ptr<Level> level;
	D3DXVECTOR3 center;
	D3DXVECTOR2 betweenCenters;
	bool movingRight;
	float speed;

	int alive;

	random_device rd;
    mt19937 gen;
public:
	EnemyGrid(void);
	~EnemyGrid(void);

	bool Init(D3DXVECTOR3 center, shared_ptr<Level> level);

	shared_ptr<Shooter> GetEnemy(int i){return grid[i];}

	void MoveBy(D3DXVECTOR3 vec);
	void OnLoop(float frameLength);
	void Fire(float frameLength);
	void CollideWith(list<InstanceEntity> &bullets);
	D3DXVECTOR3 GetPos(){return center;}

	float GetRightBorder(){return center.x + betweenCenters.x / 2;}
	float GetLeftBorder(){return center.x - betweenCenters.x / 2;}
	float GetTopBorder(){return center.y + betweenCenters.y / 2;}
	float GetBottomBorder(){return center.y - betweenCenters.y / 2;}

	//returns true if there's an enemy at pos and the enemy by &enemy
	bool GetEnemyAt(Entity bullet, shared_ptr<Shooter> &enemy);
	bool IsInBounds(D3DXVECTOR3 pos);

	list<Entity> &getBullets(){return bullets;}

	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);

	int getAliveCount(){return alive;}
};