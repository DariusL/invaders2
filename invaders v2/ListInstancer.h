#pragma once
#include "baseinstancer.h"
#include "IInstance.h"
template<class Data>
class ListInstancer : public BaseInstancer<Data>
{
public:
	ListInstancer(void);
	~ListInstancer(void);

	void SetData(list<IInstance<Data>> &instances);
};

