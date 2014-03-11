#include "includes.h"
#include "Grid.h"
#include "Direct3D.h"
#include "GameEntity.h"

Grid::Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, int columnCount, Collider &collider)
:time(800), 
downOff(1.2f), 
worldWidth(worldWidth),
movement(pos - Utils::VectorSet(width / 2.0f), pos + Utils::VectorSet(worldWidth / 2.0f - width), time / 2),
dir(RIGHT), 
columnCount(columnCount), 
width(width),
lastDrop(0),
dropFreq(2000),
collider(collider)
{
	float off = width / (columnCount - 1);
	auto first = movement.GetPos();
	instancers.emplace(RM::MODEL_PLAYER, e::make_unique<GameEntityList>(device, RM::Get().GetModel(RM::MODEL_PLAYER), RM::Get().GetShader<ColorInstancedShader>(), 50));
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
	movement.Loop(frame);
	auto pos = movement.GetPos();
	float drop = 0.0f;
	if (movement.IsOver())
	{
		if (lastDrop >= dropFreq)
		{
			drop = downOff;
			lastDrop = 0;
		}
		if (dir == LEFT)
		{
			dir = RIGHT;
			movement = Movement(pos, Utils::VectorSet(worldWidth / 2.0f - width, this->first.y - drop), this->time);
		}
		else
		{
			dir = LEFT;
			movement = Movement(pos, Utils::VectorSet(worldWidth / -2.0f, this->first.y - drop), this->time);
		}
	}
	MoveTo(pos);
	if (drop > 0.0f)
		AddRow();
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
	//bad me
	movement.MoveBy(Utils::VectorSet(0.0f, downOff));
	auto first = e::XMLoadFloat3(&this->first);
	for (int i = 0; i < columnCount; i++)
	{
		auto type = RM::MODEL_PLAYER;
		auto currentPos = first + Utils::VectorSet(off * i);
		auto enemy = e::make_shared<GameEntity>(currentPos, RM::Get().GetModel(type).GetSize(), 10, 100, 10);
		instancers[type]->Add(enemy);
		collider.InsertSecond(enemy);
	}
}