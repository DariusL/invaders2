#include "includes.h"
#include "SettingsAttribute.h"
#include "StringPool.h"

SettingsAttribute::SettingsAttribute(e::XMVECTOR pos, e::string text, float width, Settings::KEY settingsKey, int min, int max, float scale)
	:Attribute(pos, text, width, Settings::Get().Decode(settingsKey)),
	settingsKey(settingsKey),
	pressRegister(Input::ACTION_ENTER),
	left(Input::ACTION_LEFT),
	right(Input::ACTION_RIGHT)
{
	this->min = min;
	this->max = max;
	this->set = Settings::Get().GetValue(settingsKey);
	this->color = name.GetColor();
}

bool SettingsAttribute::Loop(InputType input)
{
	if (enabled)
	{
		if (pressRegister.Register(input))
			Next();
		else if (right.Register(input))
			Next();
		else if (left.Register(input))
			Prev();
	}
	return pressRegister.IsDown(input) || right.IsDown(input) || left.IsDown(input);
}


void SettingsAttribute::Prev()
{
	if (set == min)
		set = max;
	else
		set--;
	Invalidate();
}

void SettingsAttribute::Next()
{
	if (set == max)
		set = min;
	else
		set++;
	Invalidate();
}

void SettingsAttribute::Invalidate()
{
	auto &s = Settings::Get();
	s.SetValue(settingsKey, set);
	value.SetModel(StringPool::Get().GetString(s.Decode(settingsKey)));
}

void SettingsAttribute::Enable(bool enabled)
{
	this->enabled = enabled;
	name.SetColor(enabled ? color : Gray);
	value.SetColor(enabled ? color : Gray);
}