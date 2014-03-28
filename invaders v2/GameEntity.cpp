#include "includes.h"
#include "GameEntity.h"
using namespace e;

GameEntity::GameEntity(e::XMVECTOR pos, e::XMFLOAT2 size, int health, int damage, int fireRate, float speed)
:size(size), health(health), maxHealth(health), damage(damage), fireRate(fireRate), speed(speed), lastFired(0)
{
	e::XMStoreFloat3(&this->pos, pos);
}

bool GameEntity::CollidesWith(const GameEntity &other)
{
	return (abs(pos.x - other.pos.x) <= (size.x + other.size.x) / 2.0f)
		&& (abs(pos.y - other.pos.y) <= (size.y + other.size.y) / 2.0f);
}

void GameEntity::MoveBy(e::XMFLOAT3 step)
{
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + XMLoadFloat3(&step));
}

void GameEntity::MoveBy(e::XMVECTOR step)
{
	XMStoreFloat3(&pos, XMLoadFloat3(&pos) + step);
}

void GameEntity::MoveTo(e::XMFLOAT3 pos)
{
	this->pos = pos;
}

void GameEntity::MoveTo(e::XMVECTOR pos)
{
	XMStoreFloat3(&this->pos, pos);
}

bool GameEntity::Fire()
{
	if (IsDead())
		return false;
	int now = clock();
	if (lastFired + fireRate <= now)
	{
		lastFired = now;
		return true;
	}
	return false;
}