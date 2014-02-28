#include "includes.h"
#include "EnemyList.h"

EnemyList::EnemyList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount)
:BaseInstancer(device, model, shader, maxObjectCount)
{
}

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
	if (enemies.size() >= capacity)
		SetCapacity(capacity * 2);
}

void EnemyList::MoveBy(e::XMVECTOR pos)
{
	for (auto &enemy : enemies)
		enemy.MoveBy(pos);
}