#include "EnemyGrid.h"


EnemyGrid::EnemyGrid(void)
{
}


EnemyGrid::~EnemyGrid(void)
{
}

bool EnemyGrid::Init(int width, int height, D3DXVECTOR3 start)
{
	pos = start;
	gridHeight = height;
	gridWidth = width;
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			grid.push_back(make_shared<Player>(start + D3DXVECTOR3(i * 3, j * -3, 0)));
	return true;
}

void EnemyGrid::MoveBy(D3DXVECTOR3 vec)
{
	pos += vec;
	for(int i = 0; i < gridHeight*gridWidth; i++)
		grid[i]->MoveBy(vec);
}