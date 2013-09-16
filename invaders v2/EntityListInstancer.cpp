#include "includes.h"
#include "EntityListInstancer.h"


EntityListInstancer::EntityListInstancer(shared_ptr<Model> model, int maxInstanceCount): BaseInstancer(model, maxInstanceCount, sizeof(InstanceType))
{
}


EntityListInstancer::~EntityListInstancer(void)
{
}


void EntityListInstancer::SetData(list<InstanceEntity> &instances)
{
	InstanceType instance;
	instanceCount = 0;

	for(auto &x : instances)
	{
		if(instanceCount >= maxInstanceCount)
			break;
		instance = x.GetInstanceData();
		memcpy(instanceData.get() + instanceCount * instanceSize, &instance, instanceSize);
		instanceCount++;
	}
}