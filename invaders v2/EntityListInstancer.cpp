#include "includes.h"
#include "EntityListInstancer.h"


EntityListInstancer::EntityListInstancer(ComPtr<ID3D11Device> device, ColorModel &model, ColorInstancedShader &shader, int maxInstanceCount)
: BaseInstancer(device, model, shader, maxInstanceCount)
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