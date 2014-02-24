#pragma once

template<class it>
class IInstance
{
	virtual it GetInstanceData() = 0;
};