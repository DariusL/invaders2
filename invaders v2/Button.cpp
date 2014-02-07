#include "includes.h"
#include "Button.h"
#include "StringPool.h"
#include "ResourceManager.h"

Button::Button(e::XMVECTOR pos, e::string text, PressFunction &&callback)
:SimpleDrawableEntity(pos, SP::Get().GetString(text), RM::Get().GetShader<ColorShader>()),
callback(callback), clickRegister(KEYS_ENTER)
{
}

bool Button::Loop()
{
	if (clickRegister.Register())
		callback();
	return clickRegister.IsDown();
}