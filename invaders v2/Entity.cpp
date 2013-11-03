#include "includes.h"
#include "Entity.h"

Entity::Entity(D3DXVECTOR3 start, D3DXVECTOR2 size, float speed)
{
	this->pos = start;
	this->size = size;
	this->dead = false;
	this->speed = speed;
	this->deathTime = 0;
}

void Entity::MoveBy(D3DXVECTOR3 step)
{
	pos += step;
}

void Entity::MoveTo(D3DXVECTOR3 pos)
{
	this->pos = pos;
}

Entity::~Entity(void)
{
}

bool Entity::CollideWith(const Entity &other) const
{
	if(dead || other.dead)
		return false;
	if(abs(pos.x - other.pos.x) <= size.x / 2 + other.size.x / 2)
		if(abs(pos.y - other.pos.y) <= size.y / 2 + other.size.y / 2)
			return true;
	return false;
}

bool Entity::CollideWithAndKill(const Entity &other)
{
	if(CollideWith(other))
	{
		Kill();
		return true;
	}
	return false;
}

bool Entity::CollideWithAndKillBoth(Entity &other)
{
	if(CollideWithAndKill(other))
	{
		other.Kill();
		return true;
	}
	return false;
}

void Entity::Kill()
{
	dead = true;
	deathTime = clock() / (float)CLOCKS_PER_SEC;
}