#pragma once
#include "Attribute.h"

class Counter : public Attribute
{
	int count;
public:
	Counter(e::XMVECTOR pos, e::string text, float width, int initial = 0, float scale = 1.0f);
	Counter &operator+=(int off);
	Counter &operator-=(int off);
	Counter &operator++();
	Counter &operator--();
};