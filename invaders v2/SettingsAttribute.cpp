#include "includes.h"
#include "SettingsAttribute.h"
#include "StringPool.h"

SettingsAttribute::SettingsAttribute(e::XMVECTOR pos, e::string text, float width, Settings::KEY settingsKey, float scale)
	:Attribute(pos, text, width, Input::DecodeKey(Settings::Get().GetValue(settingsKey))),
	settingsKey(settingsKey),
	pressRegister(Input::ACTION_ENTER),
	listening(false)
{
}

bool SettingsAttribute::Loop(InputType input)
{
	if (pressRegister.Register(input))
	{
		listening = !listening;
		return true;
	}
	else
	{
		int key = Input::Get().GetLastKey();
		if (listening && !pressRegister.Pressed() && key != -1)
		{
			Settings::Get().SetValue(settingsKey, key);
			listening = false;
			auto &str = StringPool::Get().GetString(Input::DecodeKey(key));
			value.SetModel(str);

			return true;
		}
		return false;
	}
}