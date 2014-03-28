#include "includes.h"
#include "Counter.h"
#include "StringPool.h"
#include "ResourceManager.h"

Counter::Counter(e::XMVECTOR pos, e::string text, float width, int initial, float scale)
:left(KEYS_LEFT), right(KEYS_RIGHT),
count(initial), Attribute(pos, text, width, e::make_unique<ColorDrawableEntity>(Utils::VectorSet(), StringPool::Get().GetString(e::to_string(initial)), RM::Get().GetShader<ColorShader>()))	
{
}

void Counter::Delay()
{
	left.Reset();
	right.Reset();
}

bool Counter::Loop()
{
	if (left.Register())
		operator--();
	if (right.Register())
		operator++();
	return left.IsDown() || right.IsDown();
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
	value = e::make_unique<ColorDrawableEntity>(ValuePos(str.GetSize().x), str, RM::Get().GetShader<ColorShader>());
}