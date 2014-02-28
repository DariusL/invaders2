#include "includes.h"
#include "Grid.h"
#include "Direct3D.h"

Grid::Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, int columnCount)
:time(2000), 
downOff(0.8f), 
worldWidth(worldWidth),
movement(pos - Utils::VectorSet(width / 2.0f), pos + Utils::VectorSet(worldWidth / 2.0f - width), time / 2),
dir(RIGHT), 
columnCount(columnCount), 
width(width),
lastDrop(0),
dropFreq(500)
{
	float off = width / (columnCount - 1);
	auto first = movement.GetPos();
	instancers.emplace(RM::MODEL_PLAYER, e::make_unique<EnemyList>(device, RM::Get().GetModel(RM::MODEL_PLAYER), RM::Get().GetShader<ColorInstancedShader>(), 50));
	e::XMStoreFloat3(&this->first, first);
	AddRow();
}

void Grid::Render(const RenderParams &params)
{
	for (auto &i : instancers)
		i.second->Render(params);
}

void Grid::Loop(int frame)
{
	lastDrop += frame;
	if (lastDrop >= dropFreq)
	{
		lastDrop = 0;
		AddRow();
	}
	movement.Loop(frame);
	auto pos = movement.GetPos();
	if (movement.IsOver())
	{
		if (dir == LEFT)
		{
			dir = RIGHT;
			movement = Movement(pos, Utils::VectorSet(worldWidth / 2.0f - width, this->first.y), this->time);
		}
		else
		{
			dir = LEFT;
			movement = Movement(pos, Utils::VectorSet(worldWidth / -2.0f, this->first.y), this->time);
		}
	}
	MoveTo(pos);
}

void Grid::MoveTo(e::XMVECTOR pos)
{
	auto off = pos - e::XMLoadFloat3(&this->first);
	for (auto &instancer : instancers)
		instancer.second->MoveBy(off);
	XMStoreFloat3(&this->first, pos);
}

void Grid::AddRow()
{
	float off = width / (columnCount - 1);
	this->first.y += downOff;
	auto first = e::XMLoadFloat3(&this->first);
	for (int i = 0; i < columnCount; i++)
	{
		auto type = RM::MODEL_PLAYER;
		auto currentPos = first + Utils::VectorSet(off * i);
		instancers[type]->Add(ShooterEntity(currentPos, RM::Get().GetModel(type).GetSize(), 0.0f, 0.0f));
	}
}