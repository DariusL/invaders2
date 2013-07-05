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

public:
	EnemyGrid(void);
	~EnemyGrid(void);

	bool Init(int width, int height, D3DXVECTOR3 start);

	int GetHeight(){return gridHeight;}
	int GetWidth(){return gridWidth;}

	shared_ptr<Player> GetEnemy(int i){return grid[i];}

	void MoveBy(D3DXVECTOR3 vec);
	D3DXVECTOR3 getPos(){return pos;}
};