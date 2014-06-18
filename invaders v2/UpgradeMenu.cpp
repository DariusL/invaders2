#include "includes.h"
#include "UpgradeMenu.h"
#include "CounterButton.h"
using namespace e;
UpgradeMenu::UpgradeMenu(e::XMVECTOR pos, e::unordered_map<int, int> playerData)
	:MenuScreen(pos, "UPGRADES"), values(e::move(playerData)),
	exp(pos + Utils::VectorSet(20.0f, -12.0f, 3.0f), "EXPERIENCE LEFT", 25.0f, values[UPGRADE_EVENT_EXP_SET])
{
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_HEALTH_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_HEALTH_SET, e::placeholders::_1)));
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_MAX_HEALTH_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_MAX_HEALTH_SET, e::placeholders::_1)));
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_EXP_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_EXP_SET, e::placeholders::_1)));
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_WEPON_DMG_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_WEPON_DMG_SET, e::placeholders::_1)));
	or.push_back(UpgradeObservers::Register(UPGRADE_EVENT_WEPON_PERIOD_SET, e::bind(&UpgradeMenu::SetProperty, this, UPGRADE_EVENT_WEPON_PERIOD_SET, e::placeholders::_1)));

	Add(e::make_unique<CounterButton>(Utils::VectorSet(), "RESTORE HEALTH", 40.0f, [=](){this->Upgrade(UPGRADE_EVENT_HEALTH_SET); }, 100));
	Add(e::make_unique<CounterButton>(Utils::VectorSet(), "MORE HEALTH", 40.0f, [=](){this->Upgrade(UPGRADE_EVENT_MAX_HEALTH_SET); }, 100));
	Add(e::make_unique<CounterButton>(Utils::VectorSet(), "MORE DAMAGE", 40.0f, [=](){this->Upgrade(UPGRADE_EVENT_WEPON_DMG_SET); }, 100));
	Add(e::make_unique<CounterButton>(Utils::VectorSet(), "FASTER GUN", 40.0f, [=](){this->Upgrade(UPGRADE_EVENT_WEPON_PERIOD_SET); }, 100));
	EnableUpgrades();
}

void UpgradeMenu::SetProperty(int key, int val)
{
	values[key] = val;
}

void UpgradeMenu::Upgrade(int key)
{
	if (values[UPGRADE_EVENT_EXP_SET] >= 100)
	{
		exp.SetCount(values[UPGRADE_EVENT_EXP_SET] - 100);
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
		case UPGRADE_EVENT_WEPON_DMG_SET:
			UpgradeObservers::Notify(UPGRADE_EVENT_WEPON_DMG_SET, values[UPGRADE_EVENT_WEPON_DMG_SET] * 2);
			UpgradeObservers::Notify(UPGRADE_EVENT_EXP_SET, values[UPGRADE_EVENT_EXP_SET] - 100);
			break;
		case UPGRADE_EVENT_WEPON_PERIOD_SET:
			UpgradeObservers::Notify(UPGRADE_EVENT_WEPON_PERIOD_SET, values[UPGRADE_EVENT_WEPON_PERIOD_SET] - 50);
			UpgradeObservers::Notify(UPGRADE_EVENT_EXP_SET, values[UPGRADE_EVENT_EXP_SET] - 100);
			break;
		default:
			break;
		}
	}
	EnableUpgrades();
}

void UpgradeMenu::RenderInternal(RenderParams &params)
{
	MenuScreen::RenderInternal(params);
	exp.Render(params);
}

void UpgradeMenu::EnableUpgrades()
{
	for (int i = 0; i < items.Count(); i++)
	{
		static_cast<CounterButton&>(*items[i]).Enable(values[UPGRADE_EVENT_EXP_SET] >= 100);
	}
}