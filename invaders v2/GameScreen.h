#pragma once
#include "includes.h"
#include "Screen.h"
#include "PressRegister.h"
#include "GameWorld.h"
#include "Counter.h"

class GameScreen : public Screen
{
	PressRegister pause, upgrade;
	GameWorld world;
	Counter score, exp;
	GameObservers::ObserverScopeRef or;
	UpgradeObservers::ObserverScopeRef ur;
public:
	GameScreen(e::XMVECTOR pos);
	void RenderInternal(const RenderParams &params);
	int LoopInternal(InputType input, int frame);
	void DelayInternal();
protected:
	virtual bool ShouldRenderParent();
private:
	void UpdateCounters(const e::shared_ptr<GameEntity> entity);
	e::unordered_map<int, int> GetPlayerData();
};