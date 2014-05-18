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
header(SP::Get().GetString(header), RM::Get().GetShader<ColorShader>(), e::make_shared<GameEntity>(e::XMVectorAdd(pos, e::XMLoadFloat3(&HEADER_POS)))),
backRegister(Input::ACTION_BACK),
items(pos, ITEM_OFF, 5),
close(false)
{
}

int MenuScreen::LoopInternal(InputType input, int frame)
{
	if (childResult == RESULT_QUIT_APP || childResult == RESULT_QUIT_TO_MAIN)
		return childResult;
	else
		childResult = RESULT_CONTINUE;
	items.Loop(input);
	if (backRegister.Register(input) || close)
		return RESULT_CLOSE;
	else
		return RESULT_CONTINUE;
}

void MenuScreen::RenderInternal(RenderParams &params)
{
	params.gray = child != nullptr;
	header.Render(params);
	items.Render(params);
	params.gray = false;
}

void MenuScreen::DelayInternal()
{
	items.Delay();
	backRegister.Reset();
}