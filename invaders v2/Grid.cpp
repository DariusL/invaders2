#include "includes.h"
#include "Grid.h"
#include "Direct3D.h"
#include "GameEntity.h"
#include "Observers.h"

Grid::Grid(ID3D11Device *device, e::XMVECTOR pos, float width, float worldWidth, uint columnCount)
	:time(800),
	downOff(1.2f),
	worldWidth(worldWidth),
	movement(pos - Utils::VectorSet(width / 2.0f), pos + Utils::VectorSet(worldWidth / 2.0f - width), time / 2),
	dir(RIGHT),
	columnCount(columnCount),
	width(width),
	lastDrop(0),
	dropFreq(2000),
	bullets(device, RM::Get().GetModel(RM::MODEL_BULLET), RM::Get().GetShader<ColorInstancedShader>(), 100, e::XMFLOAT2(0.0f, -1.0f), GAME_EVENT_ENEMY_BULLET_CREATE),
	dist(RM::MODEL_ENEMY_1, RM::MODEL_ENEMY_6),
	difficulty(0)
{
	float off = width / (columnCount - 1);
	auto first = movement.GetPos();
	for (int i = RM::MODEL_ENEMY_1; i <= RM::MODEL_ENEMY_6; i++)
	{
		instancers.emplace(i, e::make_unique<EnemyList>(device, RM::Get().GetModel((RM::MODEL)i), RM::Get().GetShader<ColorInstancedShader>(), 50));
	}
	e::XMStoreFloat3(&this->first, first);
	or = GameObservers::Register(GAME_EVENT_ENEMY_DEATH, [=](const e::shared_ptr<GameEntity> en){this->difficulty += 200; });
	AddRow();
}

void Grid::Render(RenderParams &params)
{
	for (auto &i : instancers)
		i.second->Render(params);
 	bullets.Render(params);
}

void Grid::Loop(int frame)
{
	for (auto &inst : instancers)
		inst.second->Loop(frame);
	lastDrop += frame;
	movement.Loop(frame);
	bullets.Loop(frame);
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
			movement = Movement(pos, Utils::VectorSet(worldWidth / 2.0f - width, this->first.y - drop, this->first.z), this->time);
		}
		else
		{
			dir = LEFT;
			movement = Movement(pos, Utils::VectorSet(worldWidth / -2.0f, this->first.y - drop, this->first.z), this->time);
		}
	}
	MoveTo(pos);
	if (drop > 0.0f)
		AddRow();
	Fire(frame);
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
	for (uint i = 0; i < columnCount; i++)
	{
		auto type = dist(generator);
		auto currentPos = first + Utils::VectorSet(off * i);
		auto enemy = GameEntity::MakeEnemy(currentPos, type, difficulty);
		instancers[type]->Add(enemy);
		GameObservers::Notify(GAME_EVENT_ENEMY_CREATE, enemy);
	}
}

void Grid::Fire(int frame)
{
	double prob = (double)frame * 0.25;
	e::bernoulli_distribution dist(prob < 1.0f ? prob : 1.0f);
	auto fire = e::bind(dist, generator);
	for (uint i = 0; i < columnCount / instancers.size(); i++)
	{
		for (auto &instancer : instancers)
		{
			auto enemy = instancer.second->Get(i);
			if (enemy != nullptr)
			{
				if (fire())
				{
					enemy->Fire();
				}
			}
		}
	}
}