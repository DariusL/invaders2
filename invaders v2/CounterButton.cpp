#include "includes.h"
#include "CounterButton.h"

CounterButton::CounterButton(e::XMVECTOR pos, e::string text, float width, PressFunction &&callback, int initial, float scale)
	:Counter(pos, text, width, initial, scale), callback(e::forward<PressFunction>(callback)), click(Input::ACTION_ENTER), enabled(true)
{
	this->color = name.GetColor();
}

bool CounterButton::Loop(InputType input)
{
	if (click.Register(input) && enabled)
		callback();
	return click.IsDown(input) || Counter::Loop(input);
}


void CounterButton::Enable(bool enabled)
{
	this->enabled = enabled;
	name.SetColor(enabled ? color : Gray);
	value.SetColor(enabled ? color : Gray);
}