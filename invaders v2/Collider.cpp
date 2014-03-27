#include "includes.h"
#include "Collider.h"
#include "Utils.h"
#include "Observers.h"

Collider::Collider()
{
	Observers::Register(Observers::EVENT_ENEMY_CREATE, e::bind(&Collider::InsertSecond, this, e::placeholders::_1));
	Observers::Register(Observers::EVENT_PLAYER_CREATE, e::bind(&Collider::InsertFirst, this, e::placeholders::_1));
}

void Collider::InsertFirst(e::shared_ptr<GameEntity> entity)
{
	first.push_back(entity);
}

void Collider::InsertSecond(e::shared_ptr<GameEntity> entity)
{
	second.push_back(entity);
}

void Collider::Update()
{
	Utils::RemoveIf(first, [](const e::shared_ptr<GameEntity> ent){ return ent->IsDead(); });
	Utils::RemoveIf(second, [](const e::shared_ptr<GameEntity> ent){ return ent->IsDead(); });

	if (first.size() == 0 || second.size() == 0)
		return;

	auto firstEnd = &first.back();
	auto secondEnd = &second.back();
	for (auto fp = first.data(); fp <= firstEnd; fp++)
		for (auto sp = second.data(); sp <= secondEnd; sp++)
			Collide(fp->get(), sp->get());
}

void Collider::Collide(GameEntity *first, GameEntity *second)
{
	if (first == second || first->IsDead() || second->IsDead())
		return;
	if (first->CollidesWith(*second))
	{
		first->HitFor(second->GetDamage());
		second->HitFor(first->GetDamage());
	}
}