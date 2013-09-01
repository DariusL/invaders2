#include "World.h"
#include "App.h"
#include "Logger.h"

World::World()
{
	started = false;
}

World::~World()
{
}

bool World::Start(shared_ptr<Level> level)
{
	playerStart = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	ResourceManager *rm = App::Get()->GetResourceManager();
	player = make_shared<Shooter>(rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_PLAYER), 18.0f, 0.3f, rm->GetModel(ResourceManager::Models::MODEL_PLAYER));
	player->MoveTo(playerStart);
	enemies = make_shared<EnemyGrid>();
	enemies->Init(D3DXVECTOR3(0.0f, 10.0f, 0.0f), level);
	enemiesMovingRight = true;
	lives = 3;
	started = true;
	return true;
}

void World::Stop()
{
	playerBullets.clear();
	started = false;
}

bool World::Init(ID3D11Device *device, HWND hwnd)
{
	if(!player->Init(device, hwnd))
		return false;
	if(!enemies->Init(device, hwnd))
		return false;
	playerBulletGraphics = unique_ptr<Bullets>(new Bullets());
	if(!playerBulletGraphics->Init(device, hwnd))
		return false;
	return true;
}

void World::OnLoop(int input, float frameLength)
{
	CollideBullets();
	enemies->OnLoop(frameLength);
	ResourceManager *rm = App::Get()->GetResourceManager();
	if(input != 0)
	{
		if((input & ControlCodes::LEFT_AND_RIGHT) != ControlCodes::LEFT_AND_RIGHT)
		{
			if(input & ControlCodes::LEFT && player->GetLeftBorder() > float(FIELD_WIDTH) / -2)
			{
				player->MoveBy(D3DXVECTOR3(-1.0f, 0.0f, 0.0f) * (player->GetSpeed() * frameLength));
			}
			else 
				if(input & ControlCodes::RIGHT && player->GetRightBorder() < float(FIELD_WIDTH) / 2)
				{
					player->MoveBy(D3DXVECTOR3(1.0f, 0.0f, 0.0f) * (player->GetSpeed() * frameLength));
				}
		}
		if((input & ControlCodes::FIRE) 
			&& player->GetLastFired() + player->GetFireRate() <= clock() / double(CLOCKS_PER_SEC)
			&& !player->IsDead())
		{
			player->Fire();
			playerBullets.push_back(Entity(player->GetPos(), rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_BULLET), 18.0f));
		}

	}
	if(player->IsDead())
	{
		if(lives > 0 && player->GetDeathTime() + 2 < clock() / (float)CLOCKS_PER_SEC)
		{
			lives--;
			player->Revive();
			player->MoveTo(playerStart);
		}
	}
	shared_ptr<Shooter> temp;
	for(auto &b : playerBullets)
	{
		b.MoveBy(D3DXVECTOR3(0.0f, 1.0f, 0.0f) * (b.GetSpeed() * frameLength));
		if(enemies->GetEnemyAt(b, temp))
		{
			temp->Kill();
			b.Kill();
		}
	}
	playerBullets.remove_if([](const Entity &ent){return ent.IsDead() || ent.GetBottomBorder() > FIELD_HEIGHT / 2.0f;});
}

void World::CollideBullets()
{
	list<Entity> &enemyBullets = enemies->getBullets();
	for(auto &p : playerBullets)
	{
		for(auto &e : enemyBullets)
		{
			if(p.CollidesWith(e))
			{
				p.Kill();
				e.Kill();
			}
		}
	}
}

void World::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	player->Render(context, transMatrix);
	enemies->Render(context, transMatrix);
	playerBulletGraphics->setBullets(playerBullets);
	playerBulletGraphics->Render(context, transMatrix);
}