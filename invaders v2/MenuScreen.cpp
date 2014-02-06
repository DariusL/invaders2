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
backRegister(ControlCodes::PAUSE)
{
	items.push_back(make_unique<Button>(GetNextItemPos(), "MUCH GAME", [=]{}));
	items.push_back(make_unique<Button>(GetNextItemPos(), "VERY EXCITE", [=]{}));
	items.push_back(make_unique<Button>(GetNextItemPos(), "WOW", [=]{}));
}

int MenuScreen::LoopInternal(int input, float frame)
{
	if (backRegister.Register(input))
		return RESULT_CLOSE;
	else
		return RESULT_CONTINUE;
}

void MenuScreen::RenderInternal(const RenderParams &params)
{
	header.Render(params);
	for (auto &item : items)
		item->Render(params);
}

e::XMVECTOR MenuScreen::GetNextItemPos()
{
	return XMLoadFloat3(&FIRST_ITEM_POS) + XMLoadFloat3(&ITEM_OFF) * (float)items.size();
}