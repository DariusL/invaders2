#include "includes.h"
#include "SettingsKey.h"
#include "StringPool.h"
#include "App.h"
#include "AppHandle.h"

SettingsKey::SettingsKey(e::XMVECTOR pos, e::string text, float width, Settings::KEY settingsKey, float scale)
	:Attribute(pos, text, width, Settings::Get().Decode(settingsKey)),
	settingsKey(settingsKey),
	pressRegister(Input::ACTION_ENTER),
	listening(false)
{
}

bool SettingsKey::Loop(InputType input)
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

void SettingsKey::Render(RenderParams &params)
{
	if (AppHandle::Get().Tick() || !listening)
		Attribute::Render(params);
}