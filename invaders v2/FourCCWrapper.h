#pragma once
#include "includes.h"
struct FourCCWrapper
{
	char cc[4];

	FourCCWrapper(int fourCC)
	{
		memcpy(cc, &fourCC, sizeof(int));
	}
	~FourCCWrapper(){}

	inline bool operator==(const FourCCWrapper& right) const
	{
		return memcmp(this, &right, sizeof(FourCCWrapper)) == 0;
	}

	inline bool operator==(const int& right) const
	{
		return memcmp(this, &right, sizeof(FourCCWrapper)) == 0;
	}
};

template<>
struct e::hash<FourCCWrapper>
{
	inline size_t operator()(const FourCCWrapper& value) const
	{
		return e::hash<int>()(*reinterpret_cast<const int*>(value.cc));
	}
};