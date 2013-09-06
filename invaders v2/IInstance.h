#pragma once

template<class Data>
class IInstance
{
	virtual Data GetInstanceData() = 0;
};