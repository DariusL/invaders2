#pragma once
#include "includes.h"
#include "Globals.h"
#include "Input.h"
class HoldRegister
{
	Input::ACTION key;
	int time, freq;
public:
	HoldRegister(Input::ACTION key, int freq = 125) :key(key), time(clock()), freq(freq){}
	inline void Reset(){ time = clock(); }
	bool Register(InputType input)
	{
		int now = clock();
		if (IsDown(input) && time + freq < now)
		{
			time = now;
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool IsDown(InputType input)
	{
		return input[key];
	}
};