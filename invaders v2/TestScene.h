#pragma once
#include "IWorld.h"
class TestScene : public IWorld
{
public:
	TestScene();

	int OnLoop(int input, float frameLength);
	void Render(RenderParams &params);
	void Init(ComPtr<ID3D11DeviceContext> context);
};

