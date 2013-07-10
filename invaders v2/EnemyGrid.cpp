#include "EnemyGrid.h"


EnemyGrid::EnemyGrid(void)
{
}


EnemyGrid::~EnemyGrid(void)
{
}

bool EnemyGrid::Init(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, D3DXVECTOR2 enemySize)
{
	this->center = center;
	this->gap = gap;
	this->enemySize = enemySize;
	this->betweenCenters = D3DXVECTOR2((width - 1) * (gap.x + enemySize.x), (height - 1) * (gap.y + enemySize.y));
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);
	gridHeight = height;
	gridWidth = width;
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			grid.push_back(make_shared<Entity>(topLeft + D3DXVECTOR3(j * (gap.x + enemySize.x), i * -(gap.y + enemySize.y), 0), enemySize));
	return true;
}

void EnemyGrid::MoveBy(D3DXVECTOR3 vec)
{
	center += vec;
	for(int i = 0; i < gridHeight*gridWidth; i++)
		grid[i]->MoveBy(vec);
}

bool EnemyGrid::GetEnemyAt(D3DXVECTOR3 pos, shared_ptr<Entity> &enemy)
{
	if(!IsInBounds(pos))
		return false;
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);
	D3DXVECTOR3 step = enemySize + gap;
	float x = (pos.x - topLeft.x) / step.x;
	float y = (topLeft.y - pos.y) / step.y;
	float intx, inty;
	if(abs(Utils::Trunc(x, intx)) * step.x < enemySize.x / 2)
		if(abs(Utils::Trunc(y, inty)) * step.y < enemySize.y / 2)
		{
			enemy = grid[unsigned int(intx + inty * gridWidth)];
			return true;
		}
	return false;
}

bool EnemyGrid::IsInBounds(D3DXVECTOR3 pos)
{
	return pos.x > GetLeftBorder() && pos.x < GetRightBorder() && pos.y > GetBottomBorder() && pos.y < GetTopBorder();
}