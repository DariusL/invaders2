#pragma once
#include "includes.h"
#include "Screen.h"
#include "DrawableEntity.h"
#include "Button.h"

class MenuScreen : public Screen
{
	Button button;
	int nr;
public:
	MenuScreen(e::XMFLOAT3 pos, int nr);
protected:
	virtual void RenderInternal(const RenderParams &params);
	virtual int LoopInternal(int input, float frame);
};