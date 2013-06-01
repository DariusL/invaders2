#include "World.h"


World::World(void)
{
}

World::World(unsigned int fRate)
{
	player = Player(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	frameRate = fRate;
}

void World::OnLoop(int input)
{

}