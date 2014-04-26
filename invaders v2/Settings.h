#pragma once
#include "includes.h"

class Settings
{
public:
	enum KEY
	{
		KEY_FIRE_KEY,
		KEY_LEFT_KEY,
		KEY_RIGHT_KEY,
		KEY_UP_KEY,
		KEY_DOWN_KEY,
		KEY_FORWARD_KEY,
		KEY_BACK_KEY
	};
private:
	static e::unordered_map<KEY, int> settings;
	e::wstring filename;
public:
	Settings(e::wstring filename);
	int GetValue(KEY key);
	void SetValue(KEY key, int value);
	void Store();
	void Load();
};