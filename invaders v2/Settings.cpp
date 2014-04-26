#include "includes.h"
#include "Settings.h"
#include "Utils.h"

e::unordered_map<Settings::KEY, int> Settings::settings = e::unordered_map<Settings::KEY, int>(
{
	e::make_pair(Settings::KEY_FIRE_KEY, VK_SPACE),
	e::make_pair(Settings::KEY_LEFT_KEY, VK_LEFT),
	e::make_pair(Settings::KEY_RIGHT_KEY, VK_RIGHT),
	e::make_pair(Settings::KEY_UP_KEY, VK_UP),
	e::make_pair(Settings::KEY_DOWN_KEY, VK_DOWN),
	e::make_pair(Settings::KEY_BACK_KEY, VK_ESCAPE),
	e::make_pair(Settings::KEY_FORWARD_KEY, VK_RETURN),
});

Settings::Settings(e::wstring filename)
	:filename(filename)
{
	Load();
}

void Settings::SetValue(KEY key, int value)
{
	settings[key] = value;
}

void Settings::Store()
{
	e::basic_ofstream<int> file(filename, e::ios::trunc);
	for (auto &entry : settings)
	{
		file << entry.first << entry.second;
	}
}

void Settings::Load()
{
	e::basic_ifstream<int> file(filename);
	int key, val;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> key >> val;
			settings[(KEY)key] = val;
		}
	}
}

int Settings::GetValue(KEY key)
{
	using namespace e;
	auto f = settings.find(key);
	if (f == settings.end())
	{
		AssertBool(false, L"Settings key not found " + e::to_wstring(key));
	}
	else
	{
		return f->second;
	}
}