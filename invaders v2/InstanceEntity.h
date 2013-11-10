#pragma once
#include "iinstance.h"
#include "Entity.h"
#include "Globals.h"

class InstanceEntity : public IInstance<InstanceType>, public Entity
{
public:
	~InstanceEntity(void);
	InstanceEntity(XMFLOAT3 start, XMFLOAT2 size, float speed);

	InstanceType GetInstanceData();
};