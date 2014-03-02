#include "includes.h"
#include "GameEntityList.h"

GameEntityList::GameEntityList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount)
:BaseInstancer(device, model, shader, maxObjectCount)
{
}

bool GameEntityList::Update(ID3D11DeviceContext *context)
{
	auto end = e::remove_if(enemies.begin(), enemies.end(), [](const e::shared_ptr<GameEntity> ent){ return ent->IsDead(); });
	enemies.resize(end - enemies.begin());
	instanceCount = enemies.size();
	instanceData.clear();
	for (auto &enemy : enemies)
		instanceData.push_back(enemy->GetPos());
	return BaseInstancer::Update(context);
}

void GameEntityList::Add(e::shared_ptr<GameEntity> enemy)
{
	enemies.push_back(enemy);
	if (enemies.size() >= capacity)
		SetCapacity(capacity * 2);
}

void GameEntityList::MoveBy(e::XMVECTOR pos)
{
	for (auto &enemy : enemies)
		enemy->MoveBy(pos);
}