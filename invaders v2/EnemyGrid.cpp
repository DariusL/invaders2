#include "EnemyGrid.h"
#include "World.h"
#include "App.h"
#include "ResourceManager.h"

EnemyGrid::EnemyGrid(void)
{
}


EnemyGrid::~EnemyGrid(void)
{
}

bool EnemyGrid::Init(D3DXVECTOR3 center, shared_ptr<Level> level)
{
	this->center = center;
	this->level = level;
	movingRight = true;
	speed = 15.0f;
	gen = mt19937(rd());

	this->betweenCenters = D3DXVECTOR2(
		(level->gridWidth - 1) * level->gap.x,
		(level->gridHeight - 1) * level->gap.y);
	ResourceManager *rm = App::Get()->GetResourceManager();
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);

	for(int i = 0; i < level->gridHeight; i++)
		for(int j = 0; j < level->gridWidth; j++){
			shared_ptr<Shooter> enemy = rm->GetEnemy(level->enemies[i * level->gridHeight + j]);
			enemy->MoveTo(topLeft + D3DXVECTOR3(j * level->gap.x, i * -level->gap.y, 0));
			grid.push_back(enemy);
		}
	return true;
}

bool EnemyGrid::Init(ID3D11Device* device, HWND hwnd)
{
	for(auto &a : grid)
		if(!a->Init(device, hwnd))
			return false;
	enemyBulletGraphics = unique_ptr<Bullets>(new Bullets());
	if(!enemyBulletGraphics->Init(device, hwnd))
		return false;
	return true;
}

void EnemyGrid::MoveBy(D3DXVECTOR3 vec)
{
	center += vec;
	for(int i = 0; i < level->gridHeight * level->gridWidth; i++)
		grid[i]->MoveBy(vec);
}

bool EnemyGrid::GetEnemyAt(Entity bullet, shared_ptr<Shooter> &enemy)
{
	D3DXVECTOR3 pos = bullet.GetPos();
	if(!IsInBounds(pos))
		return false;
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);

	float x = (pos.x - topLeft.x) / level->gap.x;
	float y = (topLeft.y - pos.y) / level->gap.y;
	float intx, inty;
	if(abs(Utils::Trunc(x, intx)) * level->gap.x < level->gap.x / 2)
		if(abs(Utils::Trunc(y, inty)) * level->gap.y < level->gap.y / 2)
		{
			enemy = grid[unsigned int(intx + inty * level->gridWidth)];
			if(enemy->CollidesWith(bullet))
			{
				if(enemy->IsDead())
					return false;
				return true;
			}
		}
	return false;
}

bool EnemyGrid::IsInBounds(D3DXVECTOR3 pos)
{
	return pos.x > GetLeftBorder() && pos.x < GetRightBorder() && pos.y > GetBottomBorder() && pos.y < GetTopBorder();
}

void EnemyGrid::OnLoop(float frameLength)
{
	if(GetLeftBorder() < float(World::FIELD_WIDTH) / -2)
		movingRight = true;
	else if(GetRightBorder() > float(World::FIELD_WIDTH) / 2)
		movingRight = false;
	if(movingRight)
		MoveBy(D3DXVECTOR3(1.0f, 0.0f, 0.0f) * (speed * frameLength));
	else
		MoveBy(D3DXVECTOR3(-1.0f, 0.0f, 0.0f) * (speed * frameLength));
	Fire(frameLength);
	shared_ptr<Shooter> player = App::Get()->GetWorld()->GetPlayer();
	D3DXVECTOR3 playerPos = player->GetPos();
	for(auto &b : bullets)
	{
		b.MoveBy(D3DXVECTOR3(0.0f, -1.0f, 0.0f) * (b.GetSpeed() * frameLength));
		if(player->CollidesWith(b))
		{
			b.Kill();
			player->Kill();
		}
	}
	bullets.remove_if([](const Entity &ent){return ent.IsDead() || ent.GetBottomBorder() < World::FIELD_HEIGHT / -2.0f;});
}

void EnemyGrid::Fire(float frameLength)
{
	auto d = bernoulli_distribution(0.1f * frameLength);
	for(int i = 0; i < level->gridWidth; i++)
	{
		int j;
		for(j = level->gridHeight - 1; j > 0; j--)
			if(!grid[i + j * level->gridWidth]->IsDead())
				break;
		shared_ptr<Shooter> enemy = grid[i + j * level->gridWidth];
		if(enemy->IsDead())
			continue;
		if(d(gen) && enemy->GetLastFired() + enemy->GetFireRate() <= clock() / float(CLOCKS_PER_SEC))
		{
			enemy->Fire();
			bullets.emplace_back(enemy->GetPos(), D3DXVECTOR2(0.2f, 1.5f), 5.0f);
		}
	}
}

void EnemyGrid::Render(ID3D11DeviceContext* context, D3DXMATRIX transmatrix)
{
	for(auto &a : grid)
		a->Render(context, transmatrix);
	enemyBulletGraphics->setBullets(bullets);
	enemyBulletGraphics->Render(context, transmatrix);
}