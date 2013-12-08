#include "includes.h"
#include "Entity.h"

Entity::Entity(XMFLOAT3 start, float speed, XMFLOAT2 size)
{
	this->pos = start;
	this->size = size;
	this->dead = false;
	this->speed = speed;
	this->deathTime = 0;
}

void Entity::MoveBy(XMFLOAT3 step)
{
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + XMLoadFloat3(&step));
}

void Entity::MoveTo(XMFLOAT3 pos)
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