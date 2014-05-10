#include "includes.h"
#include "CounterButton.h"

CounterButton::CounterButton(e::XMVECTOR pos, e::string text, float width, PressFunction &&callback, int initial, float scale)
	:Counter(pos, text, width, initial, scale), callback(e::forward<PressFunction>(callback)), click(Input::ACTION_ENTER)
{
}

bool CounterButton::Loop(InputType input)
{
	if (click.Register(input))
		callback();
	return click.IsDown(input) || Counter::Loop(input);
}