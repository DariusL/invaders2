#include "includes.h"
#include "Counter.h"
#include "StringPool.h"
#include "ResourceManager.h"

Counter::Counter(e::XMVECTOR pos, e::string text, float width, int initial, float scale)
:left(Input::ACTION_LEFT), right(Input::ACTION_RIGHT),
count(initial), Attribute(pos, text, width, e::to_string(initial))
{
}

void Counter::Delay()
{
	left.Reset();
	right.Reset();
}

bool Counter::Loop(InputType input)
{
	if (left.Register(input))
		operator--();
	if (right.Register(input))
		operator++();
	return left.IsDown(input) || right.IsDown(input);
}

Counter &Counter::operator+=(int off)
{
	count += off;
	SetCount(count);
	return *this;
}

Counter &Counter::operator-=(int off)
{
	count -= off;
	SetCount(count);
	return *this;
}

Counter &Counter::operator++()
{
	return operator+=(1);
}

Counter &Counter::operator--()
{
	return operator-=(1);
}

void Counter::SetCount(int count)
{
	this->count = count;
	auto &str = StringPool::Get().GetString(e::to_string(count));
	value.SetModel(str);
}