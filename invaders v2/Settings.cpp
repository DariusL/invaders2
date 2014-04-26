#include "includes.h"
#include "Settings.h"
#include "Utils.h"



Settings *Settings::instance;

Settings::Settings(e::wstring filename)
	:filename(filename)
{
	Load();
	instance = this;

	settings = e::unordered_map<Settings::KEY, int>(
	{
		e::make_pair(Settings::KEY_FIRE_KEY, VK_SPACE),
		e::make_pair(Settings::KEY_LEFT_KEY, VK_LEFT),
		e::make_pair(Settings::KEY_RIGHT_KEY, VK_RIGHT),
		e::make_pair(Settings::KEY_UP_KEY, VK_UP),
		e::make_pair(Settings::KEY_DOWN_KEY, VK_DOWN),
		e::make_pair(Settings::KEY_BACK_KEY, VK_ESCAPE),
	});
}

void Settings::SetValue(KEY key, int value)
{
	settings[key] = value;
}

void Settings::Store()
{
	e::ofstream file(filename, e::ios::trunc | e::ios::binary);
	long long magic;
	for (auto &entry : settings)
	{
		magic = entry.first;
		magic = magic << 32 | entry.second;
		file.write(reinterpret_cast<char*>(&magic), sizeof(long long));
		file.seekp(8, e::ios::cur);
	}
}

void Settings::Load()
{
	e::ifstream file(filename, e::ios::binary);
	long long magic;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file.read(reinterpret_cast<char*>(&magic), sizeof(long long));
			int key = *reinterpret_cast<int*>(&magic);
			int value = *(reinterpret_cast<int*>(&magic) + 1);
			settings[(KEY)key] = value;
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
		return -1;
	}
	else
	{
		return f->second;
	}
}