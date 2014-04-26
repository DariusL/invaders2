#pragma once
#include "Attribute.h"
#include "Settings.h"
#include "PressRegister.h"

class SettingsAttribute : public Attribute
{
	bool listening;
	PressRegister pressRegister;
	Settings::KEY settingsKey;
public:
	SettingsAttribute(e::XMVECTOR pos, e::string text, float width, Settings::KEY settingsKey, float scale = 1.0f);
	virtual bool Loop(InputType input);
	virtual void Delay(){ pressRegister.Reset(); }
};