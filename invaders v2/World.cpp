#include "World.h"


World::World(void)
{
}

World::World(unsigned int fRate)
{
	player = Player(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	test = Player(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	frameRate = fRate;
}

void World::OnLoop(int input)
{
	test.MoveBy(D3DXVECTOR3(0, 0.02, 0));
	if(input != 0){
		if(input & ControlCodes::LEFT)
			player.MoveBy(D3DXVECTOR3(-0.1, 0, 0));
		else if(input & ControlCodes::RIGHT)
			player.MoveBy(D3DXVECTOR3(0.1, 0, 0));
	}
}