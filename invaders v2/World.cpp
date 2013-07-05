#include "World.h"

World::World()
{
}

bool World::Init(unsigned int fRate)
{
	player = Player(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	enemies.Init(5, 4, D3DXVECTOR3(0, 0, 0));
	frameRate = fRate;
	enemiesMovingRight = true;
	return true;
}

void World::OnLoop(int input)
{
	if(enemies.getPos().x > -20)
		enemiesMovingRight = false;
	else if(enemies.getPos().x < -40)
		enemiesMovingRight = true;
	if(enemiesMovingRight)
		enemies.MoveBy(D3DXVECTOR3(0.05, 0, 0));
	else
		enemies.MoveBy(D3DXVECTOR3(-0.05, 0, 0));
	if(input != 0){
		if(input & ControlCodes::LEFT)
			player.MoveBy(D3DXVECTOR3(-0.1, 0, 0));
		else if(input & ControlCodes::RIGHT)
			player.MoveBy(D3DXVECTOR3(0.1, 0, 0));
	}
}