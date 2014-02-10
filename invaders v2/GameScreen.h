#pragma once
#include "includes.h"
#include "Screen.h"
#include "PressRegister.h"
#include "GameWorld.h"

class GameScreen : public Screen
{
	PressRegister pause;
	GameWorld world;
public:
	GameScreen(e::XMVECTOR pos) :Screen(pos), pause(KEYS_ESC), world(pos){}
	void RenderInternal(const RenderParams &params);
	int LoopInternal(int input, float frame);
	void DelayInternal();
};