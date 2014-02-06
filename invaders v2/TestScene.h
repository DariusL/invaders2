#pragma once
#include "includes.h"
#include "Screen.h"
#include "DrawableEntity.h"
class TestScene : public Screen
{
	vector<e::unique_ptr<IDrawable>> stuff;
public:
	TestScene();

	int Loop(int input, float frameLength);
	void Render(const RenderParams &params);
};

