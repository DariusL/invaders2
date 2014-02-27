#include "includes.h"
#include "EnemyList.h"

EnemyList::EnemyList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMVECTOR pos)
:BaseInstancer(device, model, shader, maxObjectCount)
{
	e::XMStoreFloat3(&this->pos, pos);
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
}

void EnemyList::MoveTo(e::XMVECTOR pos)
{
	auto off = pos - e::XMLoadFloat3(&this->pos);
	for (auto &enemy : enemies)
		enemy.MoveBy(off);
	e::XMStoreFloat3(&this->pos, pos);
}