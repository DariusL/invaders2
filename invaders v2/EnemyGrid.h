#pragma once
#include "Player.h"
#include <vector>
#include <memory>
using namespace std;
class EnemyGrid
{
	vector<shared_ptr<Player>> grid;
	int gridHeight;
	int gridWidth;
	D3DXVECTOR3 pos;
	D3DXVECTOR2 gap;
	D3DXVECTOR2 enemySize;
	D3DXVECTOR2 betweenCenters;

public:
	EnemyGrid(void);
	~EnemyGrid(void);

	bool Init(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, D3DXVECTOR2 enemySize);

	int GetHeight(){return gridHeight;}
	int GetWidth(){return gridWidth;}

	shared_ptr<Player> GetEnemy(int i){return grid[i];}

	void MoveBy(D3DXVECTOR3 vec);
	D3DXVECTOR3 getPos(){return pos;}

	float GetRightBorder(){return pos.x + betweenCenters.x / 2;}
	float GetLeftBorder(){return pos.x - betweenCenters.x / 2;}
};