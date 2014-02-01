#pragma once
#include "IWorld.h"
class TestScene : public IWorld
{
	SimpleDrawableEntity thing;
public:
	TestScene();

	int OnLoop(int input, float frameLength);
	void Render(RenderParams &params);
};

