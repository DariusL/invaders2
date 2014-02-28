#pragma once
#include "includes.h"
#include "MenuScreen.h"

class PauseMenu : public MenuScreen
{
	int result;
public:
	PauseMenu(e::XMVECTOR pos) : MenuScreen(pos, "GAME PAUSED"), result(RESULT_CONTINUE)
	{
		Add(make_unique<Button>(XMLoadFloat3(&ZeroVec3), "RESUME", [=]{ this->result = RESULT_CLOSE; }));
		Add(make_unique<Button>(XMLoadFloat3(&ZeroVec3), "QUIT TO MENU", [=]{ this->result = RESULT_QUIT_TO_MAIN; }));
		Add(make_unique<Button>(XMLoadFloat3(&ZeroVec3), "QUIT TO DESKTOP", [=]{ this->result = RESULT_QUIT_APP; }));
	}

	int LoopInternal(int input, int frame)
	{
		if (result == RESULT_CONTINUE)
			return MenuScreen::LoopInternal(input, frame);
		else
			return result;
	}
};