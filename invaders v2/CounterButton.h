#pragma once
#include "Counter.h"

class CounterButton : public Counter
{
public:
	using PressFunction = e::function<void()>;
private:
	PressRegister click;
	PressFunction callback;
	bool enabled;
	e::XMFLOAT4 color;
public:
	CounterButton(e::XMVECTOR pos, e::string text, float width, PressFunction &&callback, int initial = 0, float scale = 1.0f);
	virtual bool Loop(InputType input);
	virtual void Delay(){ click.Reset(); }
	void Enable(bool enabled);
	bool IsEnabled(){ return enabled; }
};