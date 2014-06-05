#pragma once

#include "includes.h"

struct SoundCacheKey
{
	e::wstring path;
	bool loopForever;

	SoundCacheKey(const e::wstring& path, bool loopForever) :
		path(path), loopForever(loopForever)
	{
	}

	bool operator==(const SoundCacheKey& other) const
	{
		return path == other.path && loopForever == other.loopForever;
	}
};

template <>
struct e::hash<SoundCacheKey>
{
	size_t operator()(const SoundCacheKey& value)
	{
		return hash<e::wstring>()(value.path) ^ hash<int>()(value.loopForever);
	}
};
