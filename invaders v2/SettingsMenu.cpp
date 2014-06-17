#include "includes.h"
#include "SettingsMenu.h"
#include "Settings.h"
#include "SettingsKey.h"
#include "SettingsAttribute.h"
#include "Direct3D.h"

SettingsMenu::SettingsMenu(e::XMVECTOR pos) : MenuScreen(pos, "SETTINGS")
{
	Add(e::make_unique<SettingsAttribute>(Utils::VectorSet(), "POST", 40.0f, Settings::KEY_POST, 0, 1));
	Add(e::make_unique<SettingsKey>(Utils::VectorSet(), "FIRE", 40.0f, Settings::KEY_FIRE_KEY));
	Add(e::make_unique<SettingsKey>(Utils::VectorSet(), "MOVE LEFT", 40.0f, Settings::KEY_LEFT_KEY));
	Add(e::make_unique<SettingsKey>(Utils::VectorSet(), "MOVE RIGHT", 40.0f, Settings::KEY_RIGHT_KEY));
	Add(e::make_unique<SettingsKey>(Utils::VectorSet(), "UPGRADE", 40.0f, Settings::KEY_UPGRADE_KEY));
	Add(e::make_unique<Button>(Utils::VectorSet(), "SAVE", e::bind(&SettingsMenu::Ok, this)));
	static_cast<SettingsAttribute&>(*items[0]).Enable(Direct3D::ComputeSupport());
}

void SettingsMenu::Ok()
{
	Settings::Get().Store();
	Close();
}

void SettingsMenu::Cancel()
{
	Settings::Get().Load();
}

int SettingsMenu::LoopInternal(InputType input, int frame)
{
	int res = MenuScreen::LoopInternal(input, frame);
	if (res != RESULT_CONTINUE)
		Cancel();
	return res;
}