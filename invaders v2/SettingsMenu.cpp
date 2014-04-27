#include "includes.h"
#include "SettingsMenu.h"
#include "Settings.h"
#include "SettingsAttribute.h"

SettingsMenu::SettingsMenu(e::XMVECTOR pos) : MenuScreen(pos, "SETTINGS")
{
	Add(e::make_unique<SettingsAttribute>(Utils::VectorSet(), "FIRE KEY", 20.0f, Settings::KEY_FIRE_KEY));
	Add(e::make_unique<Button>(Utils::VectorSet(), "SAVE", e::bind(&SettingsMenu::Ok, this)));
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