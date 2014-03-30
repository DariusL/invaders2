#include "includes.h"
#include "Input.h"
#include "Globals.h"

const e::vector<e::pair<int, Input::ACTION>> Input::keyAction = 
{
	e::make_pair(VK_UP, Input::ACTION_UP),
	e::make_pair(VK_DOWN, Input::ACTION_DOWN),
	e::make_pair(VK_LEFT, Input::ACTION_LEFT),
	e::make_pair(VK_RIGHT, Input::ACTION_RIGHT),
	e::make_pair(VK_SPACE, Input::ACTION_FIRE),
	e::make_pair(VK_RETURN, Input::ACTION_ENTER),
	e::make_pair(VK_ESCAPE, Input::ACTION_ESC)
};

Input::Input()
:actions(LAST_ACTION_ENTRY, false)
{
	e::fill(keys, keys + 255, false);
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
	return actions;
}