#include "Entity.h"

Entity::Entity()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	size = D3DXVECTOR2(0.0f, 0.0f);
	deathTime = 0;
	dead = false;
}

Entity::Entity(D3DXVECTOR3 start, D3DXVECTOR2 size)
{
	pos = start;
	this->size = size;
	dead = false;
}

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

bool Entity::CollidesWith(const Entity &other) const
{
	if(abs(pos.x - other.pos.x) <= size.x / 2 + other.size.x / 2)
		if(abs(pos.y - other.pos.y) <= size.y / 2 + other.size.y / 2)
			return true;
	return false;
}

void Entity::Kill()
{
	dead = true;
	deathTime = clock() / (float)CLOCKS_PER_SEC;
}