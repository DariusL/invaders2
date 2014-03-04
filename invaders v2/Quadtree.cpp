#include "includes.h"
#include "Quadtree.h"
#include "Utils.h"

const int Quadtree::MAX_ENTITIES = 6;

Quadtree::Quadtree(e::XMVECTOR pos, float width, float height, Quadtree *parent)
:width(width), height(height), parent(parent), split(false)
{
	e::XMStoreFloat2(&this->pos, pos);
}

void Quadtree::Insert(e::shared_ptr<GameEntity> entity)
{
	auto node = GetNode(entity);
	if (node == Quadtree::NODE_OUT_OF_BOUNDS)
	{
		if (parent)
			parent->Insert(entity);
		else
			entity->Kill();
	}
	else
	{
		if (!split && entities.size() >= MAX_ENTITIES - 1)
			Split();
		if (node == Quadtree::NODE_THIS || !split)
		{
			entities.push_back(entity);
		}
		else
		{
			nodes[node]->Insert(entity);
		}
	}
}

void Quadtree::Update()
{
	auto temp = e::move(entities);
	for (auto entity : temp)
		Insert(entity);
	if (split)
	{
		for (auto &node : nodes)
			node->Update();
	}
}

int Quadtree::GetNode(e::shared_ptr<GameEntity> entity)
{
	auto entPos = entity->GetPos();
	auto entSize = entity->GetSize();
	float offx = entPos.x - pos.x;
	float offy = entPos.y - pos.y;
	if (abs(offx) > (width - entSize.x) / 2.0f || abs(offy) > (height - entSize.y) / 2.0f)
	{
		return Quadtree::NODE_OUT_OF_BOUNDS;
	}
	if (abs(offx) < entSize.x / 2.0f || abs(offy) < entSize.y / 2.0f)
	{
		return Quadtree::NODE_THIS;
	}
	if (offx > 0)
	{
		if (offy > 0)
			return 0;
		else
			return 3;
	}
	else
	{
		if (offy > 0)
			return 1;
		else
			return 2;
	}
}

void Quadtree::Split()
{
	using namespace e;
	auto pos = e::XMLoadFloat2(&this->pos);
	float hw = width / 2.0f,
		hh = height / 2.0f,
		qw = width / 4.0f,
		qh = height / 4.0f;
	nodes[0] = e::make_unique<Quadtree>(pos + Utils::VectorSet(qw, qh), hw, hh, this);
	nodes[1] = e::make_unique<Quadtree>(pos + Utils::VectorSet(-qw, qh), hw, hh, this);
	nodes[2] = e::make_unique<Quadtree>(pos + Utils::VectorSet(-qw, -qh), hw, hh, this);
	nodes[3] = e::make_unique<Quadtree>(pos + Utils::VectorSet(qw, -qh), hw, hh, this);
	split = true;
}