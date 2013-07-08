#include "World.h"
#include "App.h"
#include "Logger.h"

World::World()
{
}

bool World::Init(unsigned int fRate)
{
	player = Player(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	enemies.Init(11, 5, D3DXVECTOR3(0, 10, 0), D3DXVECTOR2(1, 1), D3DXVECTOR2(2, 2));
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
	if(input != 0){
		if(input & ControlCodes::LEFT && player.getPos().x > FIELD_WIDTH / -2)
			player.MoveBy(D3DXVECTOR3(-0.4f, 0.0f, 0.0f));
		else if(input & ControlCodes::RIGHT && player.getPos().x < FIELD_WIDTH / 2)
			player.MoveBy(D3DXVECTOR3(0.4f, 0.0f, 0.0f));
	}
}