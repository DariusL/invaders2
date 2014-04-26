#include "includes.h"
#include "Input.h"
#include "Globals.h"
#include "Settings.h"

Input *Input::instance;

Input::Input()
:actions(LAST_ACTION_ENTRY, false)
{
	e::fill(keys, keys + 255, false);
	instance = this;
	auto &s = Settings::Get().GetSettings();
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_DOWN_KEY), ACTION_DOWN));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_BACK_KEY), ACTION_BACK));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_FIRE_KEY), ACTION_FIRE));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_UP_KEY), ACTION_UP));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_LEFT_KEY), ACTION_LEFT));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_RIGHT_KEY), ACTION_RIGHT));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_FIRE_KEY), ACTION_FIRE));
	keyAction.push_back(e::make_pair(VK_ESCAPE, ACTION_BACK));
	keyAction.push_back(e::make_pair(VK_RETURN, ACTION_ENTER));
}

Input::~Input()
{
}

void Input::KeyDown(int key)
{
	keys[key] = true;
}

void Input::KeyUp(int key)
{
	keys[key] = false;
}

const e::vector<bool> &Input::Loop()
{
	for (auto &p : keyAction)
		actions[p.second] = keys[p.first];
	for (int i = 0; i < 255; i++)
	{
		if (keys[i])
		{
			lastKey = i;
			break;
		}
	}
	return actions;
}