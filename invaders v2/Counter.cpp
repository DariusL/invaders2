#include "includes.h"
#include "Counter.h"
#include "StringPool.h"
#include "ResourceManager.h"

Counter::Counter(e::XMVECTOR pos, e::string text, float width, int initial, float scale)
	:count(initial), Attribute(pos, text, width, e::to_string(initial))
{
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