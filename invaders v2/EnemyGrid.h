#pragma once
#include "Entity.h"
#include "Utils.h"
#include <vector>
#include <memory>
using namespace std;
class EnemyGrid
{
	vector<shared_ptr<Entity>> grid;
	int gridHeight;
	int gridWidth;
	D3DXVECTOR3 center;
	D3DXVECTOR2 gap;
	D3DXVECTOR2 enemySize;
	D3DXVECTOR2 betweenCenters;

public:
	EnemyGrid(void);
	~EnemyGrid(void);

	bool Init(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, D3DXVECTOR2 enemySize);

	int GetHeight(){return gridHeight;}
	int GetWidth(){return gridWidth;}

	shared_ptr<Entity> GetEnemy(int i){return grid[i];}

	void MoveBy(D3DXVECTOR3 vec);
	D3DXVECTOR3 GetPos(){return center;}

	float GetRightBorder(){return center.x + betweenCenters.x / 2 + enemySize.x / 2;}
	float GetLeftBorder(){return center.x - betweenCenters.x / 2 - enemySize.x / 2;}
	float GetTopBorder(){return center.y + betweenCenters.y / 2 + enemySize.y / 2;}
	float GetBottomBorder(){return center.y - betweenCenters.y / 2 - enemySize.y / 2;}

	//returns true if there's an enemy at pos and the enemy by &enemy
	bool GetEnemyAt(D3DXVECTOR3 pos, shared_ptr<Entity> &enemy);
	bool IsInBounds(D3DXVECTOR3 pos);
};