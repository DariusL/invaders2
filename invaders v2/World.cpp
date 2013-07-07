#include "World.h"

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
		enemies.MoveBy(D3DXVECTOR3(0.1, 0, 0));
	else
		enemies.MoveBy(D3DXVECTOR3(-0.1, 0, 0));
	stringstream stream;
	stream << "right border = " << enemies.GetRightBorder();
	((Logger*)logger)->Log(stream.str());
	stream.str("");
	stream << "right enemy = " << enemies.GetEnemy(enemies.GetWidth() - 1)->getPos().x;
	((Logger*)logger)->Log(stream.str());
	if(input != 0){
		if(input & ControlCodes::LEFT && player.getPos().x > FIELD_WIDTH / -2)
			player.MoveBy(D3DXVECTOR3(-0.2, 0, 0));
		else if(input & ControlCodes::RIGHT && player.getPos().x < FIELD_WIDTH / 2)
			player.MoveBy(D3DXVECTOR3(0.2, 0, 0));
	}
}