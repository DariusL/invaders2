#include "World.h"
#include "App.h"
#include "Logger.h"

World::World()
{
	started = false;
	lives = 3;
}

World::~World()
{

}

bool World::Start(shared_ptr<Level> level)
{
	playerStart = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	ResourceManager *rm = App::Get()->GetResourceManager();
	player = make_shared<DrawableShooter>(rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_PLAYER), 18.0f, 0.3f, rm->GetModel(ResourceManager::Models::MODEL_PLAYER));
	player->MoveTo(playerStart);
	enemies = make_shared<EnemyGrid>();
	enemies->Init(D3DXVECTOR3(0.0f, 10.0f, 0.0f), level);
	enemiesMovingRight = true;
	started = true;
	return true;
}

void World::Stop()
{
	playerBullets.clear();
	started = false;
}

bool World::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	if(!player->Init(device))
		return false;
	if(!enemies->Init(device))
		return false;
	tempWall = make_shared<Wall>(D3DXVECTOR3(0.0f, -8.0f, 1.0f), 8, 6, rm->GetModel(ResourceManager::Models::MODEL_WALL), rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_WALL_BLOCK));
	if(!tempWall->Init(device))
		return false;
	playerBulletGraphics = unique_ptr<EntityListInstancer>(new EntityListInstancer(rm->GetModel(ResourceManager::Models::MODEL_BULLET), 100));
	if(!playerBulletGraphics->Init(device))
		return false;
	return true;
}

int World::OnLoop(int input, float frameLength)
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
			playerBullets.push_back(InstanceEntity(player->GetPos(), rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_BULLET), 18.0f));
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
	shared_ptr<DrawableShooter> temp;
	for(auto &b : playerBullets)
	{
		b.MoveBy(D3DXVECTOR3(0.0f, 1.0f, 0.0f) * (b.GetSpeed() * frameLength));
	}
	enemies->CollideWith(playerBullets);
	playerBullets.remove_if([](const Entity &ent){return ent.IsDead() || ent.GetBottomBorder() > FIELD_HEIGHT / 2.0f;});
	if(lives <= 0)
		return Result::GAME_OVER;
	if(enemies->getAliveCount() <= 0)
		return Result::NEXT_LEVEL;
	return Result::CONTINUE;
}

void World::CollideBullets()
{
	list<InstanceEntity> &enemyBullets = enemies->getBullets();
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

void World::Render(RenderParams params)
{
	player->Render(params);
	enemies->Render(params);
	playerBulletGraphics->SetData(playerBullets);
	playerBulletGraphics->Render(params);
	tempWall->Render(params);
}