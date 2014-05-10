#pragma once
#include "includes.h"
#include "Screen.h"
#include "DrawableEntity.h"
class TestScene : public Screen
{
	e::vector<e::unique_ptr<IDrawable>> stuff;
public:
	TestScene();

	int Loop(int input, int frameLength);
	void Render(RenderParams &params);
};

