#include "ListInstancer.h"


template<class Data>
ListInstancer<Data>::ListInstancer(void)
{
}


template<class Data>
ListInstancer<Data>::~ListInstancer(void)
{
}

template<class Data>
void ListInstancer<Data>::SetData(list<IInstance<Data>> &instances)
{
	instanceCount = bullets.size();

	int i = 0;

	for(auto &x : bullets)
	{
		if(i >= maxInstanceCount)
			break;
		instanceData[i].position = x.GetPos();
		i++;
	}
}