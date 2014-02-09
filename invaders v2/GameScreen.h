#pragma once
#include "includes.h"
#include "Screen.h"
#include "PressRegister.h"

class GameScreen : public Screen
{
	PressRegister pause;
public:
	GameScreen(e::XMVECTOR pos) :Screen(pos), pause(KEYS_ESC){}
	void RenderInternal(const RenderParams &params);
	int LoopInternal(int input, float frame);
	void DelayInternal();
};