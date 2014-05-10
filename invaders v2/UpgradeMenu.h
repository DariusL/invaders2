#pragma once
#include "MenuScreen.h"
#include "Observers.h"
class UpgradeMenu : public MenuScreen
{
private:
	e::vector<UpgradeObservers::ObserverScopeRef> or;
	e::unordered_map<int, int> values;
public:
	UpgradeMenu(e::XMVECTOR pos, e::unordered_map<int, int> playerData);
private:
	void SetProperty(int key, int val);
	void Upgrade(int key);
};