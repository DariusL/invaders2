#pragma once
#include "includes.h"
#include "Globals.h"
class InputRegister
{
	int mask, time, freq;
public:
	InputRegister(int mask = -1, int freq = 125) :mask(mask), time(clock()), freq(freq){}
	inline bool Register(int input = -1)
	{
		int now = clock();
		if ((input & mask) && time + freq < now)
		{
			time = now;
			return true;
		}
		else
		{
			return false;
		}
	}
	inline bool Handles(int input)
	{
		return (input & mask) != 0;
	}
};