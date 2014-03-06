#include "includes.h"
#include "Collider.h"

void Collider::Insert(e::shared_ptr<GameEntity> entity)
{
	entities.push_back(entity);
}

void Collider::Update()
{
	auto end = e::remove_if(entities.begin(), entities.end(), [](const e::shared_ptr<GameEntity> ent){ return ent->IsDead(); });
	entities.resize(end - entities.begin());

	auto vecEnd = &entities.back();
	for (auto first = entities.data(); first <= vecEnd; first++)
		for (auto second = entities.data(); second <= vecEnd; second++)
			Collide(first->get(), second->get());
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