#include "includes.h"
#include "Button.h"
#include "StringPool.h"
#include "ResourceManager.h"

Button::Button(e::XMFLOAT3 pos, e::string text, PressFunction &&callback)
:SimpleDrawableEntity(pos, SP::Get().GetString(text), RM::Get().GetShader<ColorShader>()),
callback(callback), clickRegister(ControlCodes::ENTER | ControlCodes::FIRE)
{
}

bool Button::Loop(int input)
{
	if (clickRegister.Handles(input))
	{
		if (clickRegister.Register(input))
			callback();
		return true;
	}
	return false;
}