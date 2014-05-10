#include "includes.h"
#include "UpgradeMenu.h"
#include "CounterButton.h"

UpgradeMenu::UpgradeMenu(e::XMVECTOR pos, e::unordered_map<int, int> playerData)
	:MenuScreen(pos, "UPGRADES"), values(e::move(playerData))
{
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_HEALTH_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_HEALTH_SET, e::placeholders::_1)));
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_MAX_HEALTH_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_MAX_HEALTH_SET, e::placeholders::_1)));
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_EXP_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_EXP_SET, e::placeholders::_1)));

	Add(e::make_unique<CounterButton>(Utils::VectorSet(), "RESTORE HEALTH", 40.0f, [=](){this->Upgrade(UPGRADE_EVENT_HEALTH_SET); }, 100));
	Add(e::make_unique<CounterButton>(Utils::VectorSet(), "MORE HEALTH", 40.0f, [=](){this->Upgrade(UPGRADE_EVENT_MAX_HEALTH_SET); }, 100));
}

void UpgradeMenu::SetProperty(int key, int val)
{
	values[key] = val;
}

void UpgradeMenu::Upgrade(int key)
{
	if (values[UPGRADE_EVENT_EXP_SET] > 100)
	{
		switch (key)
		{
		case UPGRADE_EVENT_HEALTH_SET:
			UpgradeObservers::Notify(UPGRADE_EVENT_HEALTH_SET, values[UPGRADE_EVENT_MAX_HEALTH_SET]);
			UpgradeObservers::Notify(UPGRADE_EVENT_EXP_SET, values[UPGRADE_EVENT_EXP_SET] - 100);
			break;
		case UPGRADE_EVENT_MAX_HEALTH_SET:
			UpgradeObservers::Notify(UPGRADE_EVENT_MAX_HEALTH_SET, values[UPGRADE_EVENT_MAX_HEALTH_SET] + 20);
			UpgradeObservers::Notify(UPGRADE_EVENT_EXP_SET, values[UPGRADE_EVENT_EXP_SET] - 100);
			break;
		default:
			break;
		}
	}
}