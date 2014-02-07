#include "includes.h"
#include "MenuScreen.h"
#include "StringPool.h"
#include "ResourceManager.h"

const e::XMFLOAT3 MenuScreen::HEADER_POS = e::XMFLOAT3(0.0f, 5.0f, 0.0f);
const e::XMFLOAT3 MenuScreen::FIRST_ITEM_POS = e::XMFLOAT3(0.0f, 3.0f, 0.0f);
const e::XMFLOAT3 MenuScreen::ITEM_OFF = e::XMFLOAT3(0.0f, -2.0f, 0.0f);
const e::XMFLOAT3 MenuScreen::FOOTER_POS = e::XMFLOAT3(0.0f, -20.0f, 0.0f);

MenuScreen::MenuScreen(e::XMVECTOR pos, e::string header)
:Screen(pos), 
header(pos + e::XMLoadFloat3(&HEADER_POS), SP::Get().GetString(header), RM::Get().GetShader<ColorShader>()),
backRegister(ControlCodes::PAUSE),
items(FIRST_ITEM_POS, ITEM_OFF)
{
	items.Add(make_unique<Button>(items.GetNextItemPos(), "MUCH GAME", [=]{this->child = make_unique<MenuScreen>(pos, "MUCH GAME"); }));
	items.Add(make_unique<Button>(items.GetNextItemPos(), "SUCH SELECT", [=]{this->child = make_unique<MenuScreen>(pos, "WOW"); }));
	items.Add(make_unique<Button>(items.GetNextItemPos(), "VERY EXCITE", [=]{this->child = make_unique<MenuScreen>(pos, "VERY EXCITE"); }));
	items.Add(make_unique<Button>(items.GetNextItemPos(), "WOW", [=]{this->child = make_unique<MenuScreen>(pos, "WOW"); }));
	items.Select(true);
}

int MenuScreen::LoopInternal(int input, float frame)
{
	items.Loop(input);
	if (backRegister.Register(input))
		return RESULT_CLOSE;
	else
		return RESULT_CONTINUE;
}

void MenuScreen::RenderInternal(const RenderParams &params)
{
	header.Render(params);
	items.Render(params);
}

void MenuScreen::DelayInternal()
{
	items.Delay();
	backRegister.Register();
}