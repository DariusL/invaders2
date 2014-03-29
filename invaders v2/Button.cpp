#include "includes.h"
#include "Button.h"
#include "StringPool.h"
#include "ResourceManager.h"

Button::Button(e::XMVECTOR pos, e::string text, PressFunction &&callback)
:ColorDrawableEntity(SP::Get().GetString(text), RM::Get().GetShader<ColorShader>(), e::make_shared<GameEntity>(pos), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)),
callback(callback), clickRegister(KEYS_ENTER)
{
}

bool Button::Loop()
{
	if (clickRegister.Register())
		callback();
	return clickRegister.IsDown();
}