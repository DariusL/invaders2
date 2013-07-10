#include "Entity.h"


Entity::Entity(void)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Entity::Entity(D3DXVECTOR3 start, D3DXVECTOR2 size)
{
	pos = start;
	this->size = size;
}

void Entity::MoveBy(D3DXVECTOR3 step)
{
	pos += step;
}

Entity::~Entity(void)
{
}
