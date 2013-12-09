#include "includes.h"
#include "InstanceEntity.h"


InstanceEntity::InstanceEntity(XMFLOAT3 start, XMFLOAT2 size, float speed): Entity(start, speed, size)
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