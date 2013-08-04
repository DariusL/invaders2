#include "World.h"
#include "App.h"
#include "Logger.h"

World::World()
{
}

World::~World()
{
}

bool World::Init()
{
	playerStart = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	ResourceManager *rm = App::Get()->GetResourceManager();
	player = Shooter(playerStart, rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_PLAYER), 18.0f, 0.3f);
	enemies.Init(11, 5, D3DXVECTOR3(0.0f, 10.0f, 0.0f), rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_ENEMY_GAP), rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_ENEMY));
	enemiesMovingRight = true;
	lives = 3;
	return true;
}

void World::OnLoop(int input, float frameLength)
{
	CollideBullets();
	enemies.OnLoop(frameLength);
	ResourceManager *rm = App::Get()->GetResourceManager();
	if(input != 0)
	{
		if((input & ControlCodes::LEFT_AND_RIGHT) != ControlCodes::LEFT_AND_RIGHT)
			if(input & ControlCodes::LEFT && player.GetLeftBorder() > float(FIELD_WIDTH) / -2)
				player.MoveBy(D3DXVECTOR3(-1.0f, 0.0f, 0.0f) * (player.GetSpeed() * frameLength));
			else if(input & ControlCodes::RIGHT && player.GetRightBorder() < float(FIELD_WIDTH) / 2)
				player.MoveBy(D3DXVECTOR3(1.0f, 0.0f, 0.0f) * (player.GetSpeed() * frameLength));
		if((input & ControlCodes::FIRE) 
			&& player.GetLastFired() + player.GetFireRate() <= clock() / double(CLOCKS_PER_SEC)
			&& !player.IsDead())
		{
			player.Fire();
			playerBullets.push_back(Entity(player.GetPos(), rm->GetHitbox(ResourceManager::Hitboxes::HITBOX_BULLET), 18.0f));
		}

	}
	if(player.IsDead())
	{
		if(lives > 0 && player.GetDeathTime() + 2 < clock() / (float)CLOCKS_PER_SEC)
		{
			lives--;
			player.Revive();
			player.MoveTo(playerStart);
		}
	}
	shared_ptr<Shooter> temp;
	for(auto &b : playerBullets)
	{
		b.MoveBy(D3DXVECTOR3(0.0f, 1.0f, 0.0f) * (b.GetSpeed() * frameLength));
		if(enemies.GetEnemyAt(b.GetPos(), temp))
		{
			temp->Kill();
			b.Kill();
		}
	}
	playerBullets.remove_if([](const Entity &ent){return ent.IsDead() || ent.GetBottomBorder() > FIELD_HEIGHT / 2.0f;});
}

void World::CollideBullets()
{
	list<Entity> enemyBullets = enemies.getBullets();
	for(auto &p : playerBullets)
		for(auto &e : enemyBullets)
		{
			if(p.CollidesWith(e))
			{
				p.Kill();
				e.Kill();
			}
		}
}