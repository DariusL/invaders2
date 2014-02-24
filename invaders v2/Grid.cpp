#include "includes.h"
#include "Grid.h"

Grid::Grid(ID3D11Device *device, e::XMVECTOR pos, e::XMFLOAT2 size, const RM::Level &level)
:Entity(pos, size)
{
	int count = level.gridHeight * level.gridWidth;
	e::XMFLOAT2 off(size.x / level.gridWidth, size.y / level.gridHeight);
	e::XMVECTOR first = pos - e::XMLoadFloat2(&size) / 2.0f;
	for (int x = 0; x < level.gridWidth; x++)
	{
		for (int y = 0; y < level.gridHeight; y++)
		{
			auto type = level.enemies[y * level.gridWidth + x];
			auto pos = first + e::XMVectorSet(off.x * x, off.y * y, 0.0f, 0.0f);
			if (instancers.find(type) == instancers.end())
			{
				instancers.emplace(type, make_unique<EnemyList>(device, RM::Get().GetModel(type), RM::Get().GetShader<ColorInstancedShader>(), count));
			}
			instancers[type]->Add(ShooterEntity(pos, RM::Get().GetModel(type).GetSize(), 0.0f, 0.0f));
		}
	}
}

void Grid::Render(const RenderParams &params)
{
	for (auto &i : instancers)
		i.second->Render(params);
}