#include "includes.h"
#include "EnemyGrid.h"
#include "GameWorld.h"
#include "App.h"
#include "ResourceManager.h"
#include "Utils.h"

EnemyGrid::EnemyGrid(void)
{
	AssertBool(false, L"This entire class has been deimplemented");
}


EnemyGrid::~EnemyGrid(void)
{
}

void EnemyGrid::Init(XMFLOAT3 center, shared_ptr<Level> level)
{
	/*this->center = center;
	this->level = level;
	movingRight = true;
	speed = 15.0f;
	gen = mt19937(rd());
	alive = 0;

	this->betweenCenters = XMFLOAT2(
		(level->gridWidth - 1) * level->gap.x,
		(level->gridHeight - 1) * level->gap.y);
	auto &rm = RM::Get();
	XMFLOAT3 topLeft = XMFLOAT3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);

	for(int i = 0; i < level->gridHeight; i++)
		for(int j = 0; j < level->gridWidth; j++){
			shared_ptr<DrawableShooter> enemy = rm.GetEnemy(level->enemies[i * level->gridHeight + j]);
			enemy->MoveTo(topLeft + XMFLOAT3(j * level->gap.x, i * -level->gap.y, 0));
			grid.push_back(enemy);
			alive++;
		}*/
}

void EnemyGrid::Init(ID3D11Device *device)
{
	/*for (auto &a : grid)
		a->Init(device);
	auto &rm = RM::Get();
	enemyBulletGraphics = unique_ptr<EntityListInstancer>(new EntityListInstancer(rm.GetModel(ResourceManager::Models::MODEL_BULLET), rm.GetShader<ColorInstancedShader>(), 100));
	enemyBulletGraphics->Init(device);*/
}

void EnemyGrid::MoveBy(XMFLOAT3 vec)
{
	/*center += vec;
	for(int i = 0; i < level->gridHeight * level->gridWidth; i++)
		grid[i]->MoveBy(vec);*/
}

bool EnemyGrid::GetEnemyAt(Entity bullet, shared_ptr<DrawableShooter> &enemy)
{
	/*XMFLOAT3 pos = bullet.GetPos();
	if(!IsInBounds(pos))
		return false;
	XMFLOAT3 topLeft = XMFLOAT3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);

	float x = (pos.x - topLeft.x) / level->gap.x;
	float y = (topLeft.y - pos.y) / level->gap.y;
	float intx, inty;
	if(abs(Utils::Trunc(x, intx)) * level->gap.x < level->gap.x / 2)
		if(abs(Utils::Trunc(y, inty)) * level->gap.y < level->gap.y / 2)
		{
			enemy = grid[unsigned int(intx + inty * level->gridWidth)];
			return enemy->CollideWithAndKillBoth(bullet);
		}*/
	return false;
}

void EnemyGrid::CollideWith(list<InstanceEntity> &bullets)
{
	/*shared_ptr<DrawableShooter> enemy;
	for(auto &a : bullets)
	{
		if(GetEnemyAt(a, enemy))
		{
			a.Kill();
			enemy->Kill();
			alive--;
		}
	}*/
}

bool EnemyGrid::IsInBounds(XMFLOAT3 pos)
{
	//return pos.x > GetLeftBorder() && pos.x < GetRightBorder() && pos.y > GetBottomBorder() && pos.y < GetTopBorder();
	return false;
}

void EnemyGrid::OnLoop(float frameLength)
{
	/*if(GetLeftBorder() < float(GameWorld::FIELD_WIDTH) / -2)
		movingRight = true;
	else if(GetRightBorder() > float(GameWorld::FIELD_WIDTH) / 2)
		movingRight = false;
	if(movingRight)
		MoveBy(XMFLOAT3(1.0f, 0.0f, 0.0f) * (speed * frameLength));
	else
		MoveBy(XMFLOAT3(-1.0f, 0.0f, 0.0f) * (speed * frameLength));
	Fire(frameLength);
	shared_ptr<DrawableShooter> player = ((GameWorld*)App::Get()->GetWorld())->GetPlayer();
	XMFLOAT3 playerPos = player->GetPos();
	for(auto &b : bullets)
	{
		b.MoveBy(XMFLOAT3(0.0f, -1.0f, 0.0f) * (b.GetSpeed() * frameLength));
		player->CollideWithAndKillBoth(b);
	}
	bullets.remove_if([](const Entity &ent){return ent.IsDead() || ent.GetBottomBorder() < GameWorld::FIELD_HEIGHT / -2.0f;});*/
}

void EnemyGrid::Fire(float frameLength)
{
	/*auto d = bernoulli_distribution(0.1f * frameLength);
	for(int i = 0; i < level->gridWidth; i++)
	{
		int j;
		for(j = level->gridHeight - 1; j > 0; j--)
			if(!grid[i + j * level->gridWidth]->IsDead())
				break;
		shared_ptr<DrawableShooter> enemy = grid[i + j * level->gridWidth];
		if(enemy->IsDead())
			continue;
		if(d(gen))
			if(enemy->Fire())
			{
				bullets.emplace_back(enemy->GetPos(), XMFLOAT2(0.2f, 1.5f), 5.0f);
			}
	}*/
}

void EnemyGrid::Render(RenderParams &params)
{
	/*for(auto &a : grid)
		a->Render(params);
	enemyBulletGraphics->SetData(bullets);
	enemyBulletGraphics->Render(params);*/
}