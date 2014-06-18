#pragma once
#include "Screen.h"
#include "DrawableEntity.h"
#include "PressRegister.h"
#include "Counter.h"

class GameOverScreen : public Screen
{
	PressRegister enter, esc;
	Counter score;
	SimpleDrawableEntity message;
public:
	GameOverScreen(e::XMVECTOR pos, int score);
	void RenderInternal(RenderParams &params);
	int LoopInternal(InputType input, int frame);
	void DelayInternal();
};