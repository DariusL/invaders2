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

bool EnemyGrid::Init(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, D3DXVECTOR2 enemySize)
{
	this->center = center;
	this->gap = gap;
	this->enemySize = enemySize;
	movingRight = true;
	speed = 15.0f;
	gen = mt19937(rd());
	
	this->betweenCenters = D3DXVECTOR2((width - 1) * (gap.x + enemySize.x), (height - 1) * (gap.y + enemySize.y));
	Model *enemyModel = App::Get()->GetResourceManager()->GetModel(ResourceManager::ModelCodes::MODEL_ENEMY);
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);
	gridHeight = height;
	gridWidth = width;
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			grid.push_back(make_shared<Shooter>(topLeft + D3DXVECTOR3(j * (gap.x + enemySize.x), i * -(gap.y + enemySize.y), 0), enemySize, 0.0f, 0.5f, enemyModel));
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
	for(int i = 0; i < gridHeight*gridWidth; i++)
		grid[i]->MoveBy(vec);
}

bool EnemyGrid::GetEnemyAt(D3DXVECTOR3 pos, shared_ptr<Shooter> &enemy)
{
	if(!IsInBounds(pos))
		return false;
	D3DXVECTOR3 topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);
	D3DXVECTOR3 step = enemySize + gap;
	float x = (pos.x - topLeft.x) / step.x;
	float y = (topLeft.y - pos.y) / step.y;
	float intx, inty;
	if(abs(Utils::Trunc(x, intx)) * step.x < enemySize.x / 2)
		if(abs(Utils::Trunc(y, inty)) * step.y < enemySize.y / 2)
		{
			enemy = grid[unsigned int(intx + inty * gridWidth)];
			if(enemy->IsDead())
				return false;
			return true;
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
		D3DXVECTOR3 bPos = b.GetPos();
		if(bPos.y >= player->GetBottomBorder() && bPos.y <= player->GetTopBorder()
			&& bPos.x >= player->GetLeftBorder() && bPos.x <= player->GetRightBorder())

			App::Get()->GetWorld()->GetPlayer()->Kill();
	}
	bullets.remove_if([](const Entity &ent){return ent.IsDead() || ent.GetBottomBorder() < World::FIELD_HEIGHT / -2.0f;});
}

void EnemyGrid::Fire(float frameLength)
{
	auto d = bernoulli_distribution(0.1f * frameLength);
	for(int i = 0; i < gridWidth; i++)
	{
		int j;
		for(j = gridHeight - 1; j > 0; j--)
			if(!grid[i + j * gridWidth]->IsDead())
				break;
		shared_ptr<Shooter> enemy = grid[i + j * gridWidth];
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