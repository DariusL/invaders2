#include "includes.h"
#include "EnemyList.h"

bool EnemyList::Update(ID3D11DeviceContext *context)
{
	instanceCount = enemies.size();
	instanceData.clear();
	for (auto &enemy : enemies)
		instanceData.push_back(enemy.GetPos());
	return BaseInstancer::Update(context);
}

void EnemyList::Add(ShooterEntity &&enemy)
{
	enemies.push_back(e::forward<ShooterEntity>(enemy));
}