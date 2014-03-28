#include "includes.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "Counter.h"
#include "StringPool.h"

class MainMenu : public MenuScreen
{
	bool quit;
public:
	MainMenu(e::XMVECTOR pos) :MenuScreen(pos, "MAIN MENU"), quit(false)
	{
		Add(make_unique<Button>(XMLoadFloat3(&ZeroVec3), "START GAME", [=]{ auto pos = XMLoadFloat3(&this->pos); this->child = make_unique<GameScreen>(pos); }));
		Add(make_unique<Button>(XMLoadFloat3(&ZeroVec3), "QUIT", [=]{ this->quit = true; }));
	}

	int LoopInternal(int input, int frame)
	{
		int res = MenuScreen::LoopInternal(input, frame);
		if (res == RESULT_QUIT_TO_MAIN)
			childResult = RESULT_CONTINUE;
		if (res == RESULT_CLOSE || res == RESULT_QUIT_APP || quit)
			return RESULT_CLOSE;
		else
			return RESULT_CONTINUE;
	}
};