#pragma once
#include "Attribute.h"
#include "Settings.h"
#include "PressRegister.h"

class SettingsAttribute : public Attribute
{
	PressRegister pressRegister, left, right;
	Settings::KEY settingsKey;
	int min, max, set;
	bool enabled;
	e::XMFLOAT4 color;
public:
	SettingsAttribute(e::XMVECTOR pos, e::string text, float width, Settings::KEY settingsKey, int min, int max, float scale = 1.0f);
	virtual bool Loop(InputType input);
	virtual void Delay(){ pressRegister.Reset(); }
	void Enable(bool enabled);
private:
	void Prev();
	void Next();
	void Invalidate();
};