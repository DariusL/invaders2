#include "includes.h"
#include "Counter.h"
#include "StringPool.h"
#include "ResourceManager.h"

Counter::Counter(e::XMVECTOR pos, e::string text, float width, int initial, float scale)
:count(count), Attribute(pos, text, width, ColorDrawableEntity(Utils::VectorSet(), StringPool::Get().GetString(e::to_string(initial)), RM::Get().GetShader<ColorShader>()))
{

}

Counter &Counter::operator+=(int off)
{
	count += off;
	return *this;
}

Counter &Counter::operator-=(int off)
{
	count -= off;
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