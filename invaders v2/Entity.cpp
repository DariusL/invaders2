#include "includes.h"
#include "Entity.h"

Entity::Entity(XMFLOAT3 start, XMFLOAT2 size, bool dead)
:pos(start), size(size), dead(dead), deathTime(0.0f)
{
	if (dead)
		Kill();
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

void Entity::Kill()
{
	dead = true;
	deathTime = clock() / (float)CLOCKS_PER_SEC;
}