#include "World.h"
#include "App.h"
#include "Logger.h"

World::World()
{
}

World::~World()
{
}

bool World::Init(unsigned int fRate)
{
	player = Entity(D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXVECTOR2(2, 2));
	player.SetFireRate(0.5);
	enemies.Init(11, 5, D3DXVECTOR3(0.0f, 10, 0.0f), D3DXVECTOR2(1, 1), D3DXVECTOR2(2, 2));
	frameRate = fRate;
	enemiesMovingRight = true;
	return true;
}

void World::OnLoop(int input)
{
	if(enemies.GetLeftBorder() < float(FIELD_WIDTH) / -2)
		enemiesMovingRight = true;
	else if(enemies.GetRightBorder() > float(FIELD_WIDTH) / 2)
		enemiesMovingRight = false;
	if(enemiesMovingRight)
		enemies.MoveBy(D3DXVECTOR3(0.2f, 0.0f, 0.0f));
	else
		enemies.MoveBy(D3DXVECTOR3(-0.2f, 0.0f, 0.0f));
	if(input != 0)
	{
		if((input & ControlCodes::LEFT_AND_RIGHT) != ControlCodes::LEFT_AND_RIGHT)
			if(input & ControlCodes::LEFT && player.GetLeftBorder() > float(FIELD_WIDTH) / -2)
				player.MoveBy(D3DXVECTOR3(-0.3f, 0.0f, 0.0f));
			else if(input & ControlCodes::RIGHT && player.GetRightBorder() < float(FIELD_WIDTH) / 2)
				player.MoveBy(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
		if(input & ControlCodes::FIRE && player.GetLastFired() + player.GetFireRate() <= clock() / double(CLOCKS_PER_SEC))
		{
			player.Fire();
			playerBullets.push_back(Entity(player.GetPos(), D3DXVECTOR2(0.2f, 1.5f)));
		}

	}
	for(auto &b : playerBullets)
		b.MoveBy(D3DXVECTOR3(0.0f, 0.3f, 0.0f));
	playerBullets.remove_if([](const Entity &ent){return ent.GetBottomBorder() > FIELD_HEIGHT / 2.0f;});
}