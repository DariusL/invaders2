#include "includes.h"
#include "GameEntityList.h"

GameEntityList::GameEntityList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMFLOAT4 color)
:BaseInstancer(device, model, shader, maxObjectCount), color(color)
{
}

GameEntityList::GameEntityList(GameEntityList &&other)
:BaseInstancer(e::move(other))
{
	e::swap(enemies, other.enemies);
}

bool GameEntityList::Update(ID3D11DeviceContext *context)
{
	instanceCount = enemies.size();
	instanceData.clear();
	for (auto &enemy : enemies)
		instanceData.push_back(enemy->GetPos());
	return BaseInstancer::Update(context);
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

void GameEntityList::Render(const RenderParams &params)
{
	if (!Update(params.context))
		return;
	model.Set(params.context);
	params.context->IASetVertexBuffers(1, 1, instanceBuffer.GetAddressOf(), instanceBuffer.GetStride(), instanceBuffer.GetOffset());
	shader.SetShaderParametersInstanced(params, color);
	shader.RenderShaderInstanced(params.context, model.GetIndexCount(), instanceCount);
}