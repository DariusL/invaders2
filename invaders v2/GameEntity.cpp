#include "includes.h"
#include "GameEntity.h"
#include "ResourceManager.h"
using namespace e;

e::default_random_engine GameEntity::gen;
e::uniform_int_distribution<int> GameEntity::dist;

GameEntity::GameEntity(e::XMVECTOR pos, int health, int damage, float speed, e::XMFLOAT2 size, e::unique_ptr<Gun> gun, e::XMFLOAT4 color)
	:health(health), maxHealth(health), damage(damage), speed(speed), size(size), gun(e::move(gun)), color(color)
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

void GameEntity::Fire()
{
	if (!IsDead())
		gun->Fire(e::XMLoadFloat3(&this->pos));
}

e::shared_ptr<GameEntity> GameEntity::MakeEnemy(e::XMVECTOR pos, int model, int difficulty)
{
	int initialMax = difficulty / 2;

	auto mx = [=](int diff){return diff > initialMax ? initialMax : diff; };
	auto maybeMod = [](int a, int b){if (b == 0) return 0; else return a % b; };

	int health = 1 + maybeMod(dist(gen), mx(difficulty));
	difficulty -= health;
	int damage = 10 + maybeMod(dist(gen), mx(difficulty));
	difficulty -= damage;
	int firePeriod = maybeMod(dist(gen), mx(difficulty));
	difficulty -= firePeriod;
	firePeriod = 3000 - firePeriod * 10;

	return make_shared<GameEntity>(pos, health, damage, 0.0f, RM::Get().GetModel((RM::MODEL)model).GetSize(), Gun::EnemyGun(firePeriod, damage));
}

e::XMFLOAT4 GameEntity::GetColor()
{
	int health = this->health + 100;
	int mask = (1 << 16) - 1;
	float b = float(health & mask) / 255.0f;
	mask <<= 16;
	float g = float(health & mask) / 255.0f;
	mask <<= 16;
	float r = float(health & mask) / 255.0f;
	return e::XMFLOAT4(r, g, b, 1.0f);
}