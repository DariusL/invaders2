#include "InstanceEntity.h"


InstanceEntity::InstanceEntity(void)
{
}


InstanceEntity::~InstanceEntity(void)
{
}

InstanceType InstanceEntity::GetInstanceData()
{
	InstanceType ret;
	ret.position = pos;
	return ret;
}