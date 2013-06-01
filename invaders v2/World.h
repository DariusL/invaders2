#pragma once
#include "Player.h"
#include <D3D11.h>

class World
{
public:
	World();
	World(unsigned int fRate);

	void OnLoop(int input);
	D3DXVECTOR3 GetPlayerPos(){return player.getPos();}
private:
	Player player;
	int frameRate;
};