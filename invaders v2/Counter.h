#pragma once
#include "Attribute.h"
#include "PressRegister.h"

class Counter : public Attribute
{
	int count;
public:
	Counter(e::XMVECTOR pos, e::string text, float width, int initial = 0, float scale = 1.0f);
	void SetCount(int count);
	int GetValue(){ return count; }
	Counter &operator+=(int off);
	Counter &operator-=(int off);
	Counter &operator++();
	Counter &operator--();
};