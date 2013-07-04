#pragma once
#include "Player.h"
#include "Globals.h"
#include <D3D11.h>

class World
{
public:
	World();
	World(unsigned int fRate);

	void OnLoop(int input);
	D3DXVECTOR3 GetPlayerPos(){return player.getPos();}
	D3DXVECTOR3 GetTestPos(){return test.getPos();}
private:
	Player player;
	Player test;
	int frameRate;
};