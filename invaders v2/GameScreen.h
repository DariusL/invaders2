#pragma once
#include "includes.h"
#include "Screen.h"
#include "PressRegister.h"
#include "GameWorld.h"
#include "Counter.h"

class GameScreen : public Screen
{
	GameObservers gameObservers;
	PressRegister pause;
	GameWorld world;
	Counter score, exp;
public:
	GameScreen(e::XMVECTOR pos);
	void RenderInternal(const RenderParams &params);
	int LoopInternal(InputType input, int frame);
	void DelayInternal();
private:
	void UpdateCounters(const e::shared_ptr<GameEntity> entity);
};