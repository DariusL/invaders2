#include "includes.h"
#include "InstanceEntity.h"


InstanceEntity::InstanceEntity(D3DXVECTOR3 start, D3DXVECTOR2 size, float speed): Entity(start, size, speed)
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