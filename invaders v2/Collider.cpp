#include "includes.h"
#include "Collider.h"

void Collider::Add(e::shared_ptr<GameEntity> entity)
{
	entities.push_back(entity);
}

void Collider::Update()
{
	auto end = e::remove_if(entities.begin(), entities.end(), [](const e::shared_ptr<GameEntity> ent){ return ent->IsDead(); });
	entities.resize(end - entities.begin());

}