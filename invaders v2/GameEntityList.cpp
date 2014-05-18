#include "includes.h"
#include "GameEntityList.h"

GameEntityList::GameEntityList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount)
:BaseInstancer(device, model, shader, maxObjectCount)
{
}

GameEntityList::GameEntityList(GameEntityList &&other)
:BaseInstancer(e::move(other))
{
	e::swap(enemies, other.enemies);
}

void GameEntityList::Loop(int frame)
{
	Utils::RemoveIf(enemies, [this](const e::shared_ptr<GameEntity> ent)
	{
		if (ent->IsDead())
		{
			OnRemove(ent);
			return true;
		}
		else
		{
			return false;
		}
	});
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

e::shared_ptr<GameEntity> GameEntityList::Get(uint i)
{
	if (i < enemies.size())
		return enemies[i];
	else
		return nullptr;
}

void GameEntityList::Render(RenderParams &params)
{
	InstanceType it;
	instanceCount = enemies.size();
	instanceData.clear();
	for (auto &enemy : enemies)
	{
		it.color = enemy->GetColor();
		it.position = enemy->GetPos();
		instanceData.push_back(it);
	}
		
	if (!Update(params.context))
		return;
	model.Set(params.context);
	params.context->IASetVertexBuffers(1, 1, instanceBuffer.GetAddressOf(), instanceBuffer.GetStride(), instanceBuffer.GetOffset());
	shader.SetShaderParametersInstanced(params);
	shader.RenderShaderInstanced(params.context, model.GetIndexCount(), instanceCount);
}