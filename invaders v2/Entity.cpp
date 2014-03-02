#include "includes.h"
#include "Entity.h"
using namespace e;

Entity::Entity(XMFLOAT3 start)
:pos(start)
{
}

Entity::Entity(XMVECTOR start)
{
	XMStoreFloat3(&pos, start);
}

void Entity::MoveBy(XMFLOAT3 step)
{
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + XMLoadFloat3(&step));
}

void Entity::MoveBy(XMVECTOR step)
{
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + step);
}

void Entity::MoveTo(XMFLOAT3 pos)
{
	this->pos = pos;
}

void Entity::MoveTo(XMVECTOR pos)
{
	XMStoreFloat3(&this->pos, pos);
}