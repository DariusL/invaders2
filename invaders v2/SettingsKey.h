#pragma once
#include "Attribute.h"
#include "Settings.h"
#include "PressRegister.h"

class SettingsKey : public Attribute
{
	bool listening;
	PressRegister pressRegister;
	Settings::KEY settingsKey;
public:
	SettingsKey(e::XMVECTOR pos, e::string text, float width, Settings::KEY settingsKey, float scale = 1.0f);
	virtual bool Loop(InputType input);
	virtual void Delay(){ pressRegister.Reset(); }
	virtual void Render(RenderParams &params);
};