#pragma once
#include "IWorld.h"
class TestScene : public IWorld
{
	vector<unique_ptr<IDrawable>> stuff;
public:
	TestScene();

	int OnLoop(int input, float frameLength);
	void Render(RenderParams &params);
};

