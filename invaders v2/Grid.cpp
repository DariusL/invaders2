#include "includes.h"
#include "Grid.h"

Grid::Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, int columnCount)
:Entity(pos, e::XMFLOAT2(width, 0.0f)), time(2000), downOff(0.8f), worldWidth(worldWidth),
movement(pos, pos + Utils::VectorSet((worldWidth - width) / 2.0f), time / 2), dir(RIGHT), columnCount(columnCount), width(width)
{
	float off = width / (columnCount - 1);
	e::XMVECTOR first = pos - Utils::VectorSet(width / 2.0f);
	for (int i = 0; i < columnCount; i++)
	{
		auto type = RM::MODEL_PLAYER;
		auto currentPos = first + Utils::VectorSet(off * i);
		if (instancers.find(type) == instancers.end())
		{
			instancers.emplace(type, e::make_unique<EnemyList>(device, RM::Get().GetModel(type), RM::Get().GetShader<ColorInstancedShader>(), 50, pos));
		}
		instancers[type]->Add(ShooterEntity(currentPos, RM::Get().GetModel(type).GetSize(), 0.0f, 0.0f));
	}

}

void Grid::Render(const RenderParams &params)
{
	for (auto &i : instancers)
		i.second->Render(params);
}

void Grid::Loop(int frame)
{
	movement.Loop(frame);
	auto pos = movement.GetPos();
	if (movement.IsOver())
	{
		if (dir == LEFT)
		{
			dir = RIGHT;
			movement = Movement(pos, Utils::VectorSet((worldWidth - width) / 2.0f, this->pos.y), this->time);
		}
		else
		{
			dir = LEFT;
			movement = Movement(pos, Utils::VectorSet((worldWidth - width) / -2.0f, this->pos.y), this->time);
		}
	}
	MoveTo(pos);
}

void Grid::MoveTo(e::XMVECTOR pos)
{
	for (auto &instancer : instancers)
		instancer.second->MoveTo(pos);
	XMStoreFloat3(&this->pos, pos);
}