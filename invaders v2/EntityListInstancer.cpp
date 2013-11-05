#include "includes.h"
#include "EntityListInstancer.h"


EntityListInstancer::EntityListInstancer(shared_ptr<ColorModel> model, ColorInstancedShader &shader, int maxInstanceCount): BaseInstancer(model, shader, maxInstanceCount)
{
}


EntityListInstancer::~EntityListInstancer(void)
{
}


void EntityListInstancer::SetData(list<InstanceEntity> &instances)
{
	instanceCount = 0;

	for(auto &x : instances)
	{
		if(instanceCount >= maxInstanceCount)
			break;
		instanceData[instanceCount] = x.GetInstanceData();
		instanceCount++;
	}
}