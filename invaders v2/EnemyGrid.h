#pragma once
#pragma warning(disable : 4005)

#include <vector>
#include <memory>
#include <list>
#include <random>

#include "IDrawable.h"
#include "Level.h"
#include "Globals.h"
#include "DrawableShooter.h"
#include "InstanceEntity.h"
#include "EntityListInstancer.h"

using namespace std;
class EnemyGrid : public IDrawable
{
	vector<shared_ptr<DrawableShooter>> grid;

	list<InstanceEntity> bullets;
	unique_ptr<EntityListInstancer> enemyBulletGraphics;

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

	shared_ptr<DrawableShooter> GetEnemy(int i){return grid[i];}

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
	bool GetEnemyAt(Entity bullet, shared_ptr<DrawableShooter> &enemy);
	bool IsInBounds(D3DXVECTOR3 pos);

	list<InstanceEntity> &getBullets(){return bullets;}

	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);

	int getAliveCount(){return alive;}
};