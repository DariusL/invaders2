#pragma once
#include "includes.h"

class Settings
{
public:
	enum KEY
	{
		KEY_FIRE_KEY = 0,
		KEY_LEFT_KEY = 1,
		KEY_RIGHT_KEY = 2,
		KEY_UP_KEY = 3,
		KEY_DOWN_KEY = 4,
		KEY_BACK_KEY = 5,
		KEY_UPGRADE_KEY = 6,
		KEY_POST = 7
	};
private:
	e::unordered_map<KEY, int> settings;
	e::wstring filename;
	static Settings *instance;
public:
	Settings(e::wstring filename);
	int GetValue(KEY key);
	void SetValue(KEY key, int value);
	void Store();
	void Load();
	static Settings &Get(){ return *instance; }
	const e::unordered_map<KEY, int> &GetSettings(){ return settings; }
	e::string Decode(KEY key);
};