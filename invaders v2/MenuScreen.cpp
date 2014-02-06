#include "includes.h"
#include "MenuScreen.h"

MenuScreen::MenuScreen(e::XMFLOAT3 pos, int nr)
:nr(nr), Screen(pos), 
button(pos, "MENU " + nr, [=]()
{
	this->child = make_unique<MenuScreen>(pos, nr + 1);
})
{
}

int MenuScreen::LoopInternal(int input, float frame)
{
	if (input & ControlCodes::PAUSE)
		return RESULT_CLOSE;
	button.Loop(input);
	return RESULT_CONTINUE;
}

void MenuScreen::RenderInternal(const RenderParams &params)
{
	button.Render(params);
}