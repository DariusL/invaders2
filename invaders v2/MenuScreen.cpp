#include "includes.h"
#include "MenuScreen.h"
#include "StringPool.h"
#include "ResourceManager.h"

const e::XMFLOAT3 MenuScreen::HEADER_POS = e::XMFLOAT3(0.0f, 5.0f, 0.0f);
const e::XMFLOAT3 MenuScreen::FIRST_ITEM_POS = e::XMFLOAT3(0.0f, 10.0f, 0.0f);
const float MenuScreen::ITEM_OFF = 2.0f;
const e::XMFLOAT3 MenuScreen::FOOTER_POS = e::XMFLOAT3(0.0f, -20.0f, 0.0f);

MenuScreen::MenuScreen(e::XMVECTOR pos, e::string header)
:Screen(pos), 
header(pos + e::XMLoadFloat3(&HEADER_POS), SP::Get().GetString(header), RM::Get().GetShader<ColorShader>()),
backRegister(ControlCodes::PAUSE)
{
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
}