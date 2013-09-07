#include "EntityListInstancer.h"


EntityListInstancer::EntityListInstancer(shared_ptr<Model> model, int maxInstanceCount): BaseInstancer(model, maxInstanceCount, sizeof(InstanceType))
{
}


EntityListInstancer::~EntityListInstancer(void)
{
}


void EntityListInstancer::SetData(list<InstanceEntity> &instances)
{
	instanceCount = instances.size();
	InstanceType instance;
	int i = 0;

	for(auto &x : instances)
	{
		if(i >= maxInstanceCount)
			break;
		instance = x.GetInstanceData();
		memcpy(instanceData.get() + i * instanceSize, &instance, instanceSize);
		i++;
	}
}