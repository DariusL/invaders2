#include "ShooterListInstancer.h"


ShooterListInstancer::ShooterListInstancer(shared_ptr<Model> model, int maxInstanceCount): BaseInstancer(model, maxInstanceCount, sizeof(InstanceType))
{
}


ShooterListInstancer::~ShooterListInstancer(void)
{
}


void ShooterListInstancer::SetData(list<InstanceShooter> &instances)
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