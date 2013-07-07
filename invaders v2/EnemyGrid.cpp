#include "EnemyGrid.h"


EnemyGrid::EnemyGrid(void)
{
}


EnemyGrid::~EnemyGrid(void)
{
}

bool EnemyGrid::Init(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, D3DXVECTOR2 enemySize)
{
	pos = center;
	this->gap = gap;
	this->enemySize = enemySize;
	this->betweenCenters = D3DXVECTOR2((width - 1) * (gap.x + enemySize.x), (height - 1) * (gap.y + enemySize.y));
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0, center.y + betweenCenters.y / 2.0, 0);
	gridHeight = height;
	gridWidth = width;
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			grid.push_back(make_shared<Player>(topLeft + D3DXVECTOR3(j * (gap.x + enemySize.x), i * -(gap.y + enemySize.y), 0)));
	return true;
}

void EnemyGrid::MoveBy(D3DXVECTOR3 vec)
{
	pos += vec;
	for(int i = 0; i < gridHeight*gridWidth; i++)
		grid[i]->MoveBy(vec);
}