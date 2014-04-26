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
		KEY_BACK_KEY
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
};