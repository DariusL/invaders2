#pragma once
#include "MenuScreen.h"
#include "Observers.h"
#include "Counter.h"
class UpgradeMenu : public MenuScreen
{
private:
	e::vector<UpgradeObservers::ObserverScopeRef> or;
	e::unordered_map<int, int> values;
	Counter exp;
public:
	UpgradeMenu(e::XMVECTOR pos, e::unordered_map<int, int> playerData);
protected:
	void SetProperty(int key, int val);
	void Upgrade(int key);
	void RenderInternal(RenderParams &params);
	void EnableUpgrades();
};