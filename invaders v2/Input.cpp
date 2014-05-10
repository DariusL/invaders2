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
}

Input::~Input()
{
}

void Input::LoadKeys()
{
	auto &s = Settings::Get().GetSettings();
	keyAction.clear();
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_DOWN_KEY), ACTION_DOWN));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_BACK_KEY), ACTION_BACK));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_FIRE_KEY), ACTION_FIRE));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_UP_KEY), ACTION_UP));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_LEFT_KEY), ACTION_LEFT));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_RIGHT_KEY), ACTION_RIGHT));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_FIRE_KEY), ACTION_FIRE));
	keyAction.push_back(e::make_pair(s.at(Settings::KEY_UPGRADE_KEY), ACTION_UPGRADE));
	keyAction.push_back(e::make_pair(VK_ESCAPE, ACTION_BACK));
	keyAction.push_back(e::make_pair(VK_RETURN, ACTION_ENTER));
}

void Input::KeyDown(int key)
{
	keys[key] = true;
	//OutputDebugStringA((e::to_string(key) + " down\n").c_str());
}

void Input::KeyUp(int key)
{
	keys[key] = false;
	//OutputDebugStringA((e::to_string(key) + " up\n").c_str());
}

const e::vector<bool> &Input::Loop()
{
	lastKey = -1;
	e::fill(actions.begin(), actions.end(), false);
	for (auto &p : keyAction)
		actions[p.second] = keys[p.first];
	for (int i = 0; i < 255; i++)
	{
		if (keys[i] && i != VK_RETURN && i != VK_ESCAPE)
		{
			lastKey = i;
			break;
		}
	}
	return actions;
}

e::string Input::DecodeKey(int key)
{
	switch (key)
	{
	case VK_SPACE:
		return "SPACE";
	case VK_RETURN:
		return "ENTER";
	case VK_LEFT:
		return "LEFT";
	case VK_RIGHT:
		return "RIGHT";
	case VK_DOWN:
		return "DOWN";
	case VK_UP:
		return "UP";
	case VK_ESCAPE:
		return "ESCAPE";
	default:
		return e::string(reinterpret_cast<char*>(&key), 1);
	}
}