#pragma once
#include "iinstance.h"
#include "Entity.h"
#include "Globals.h"

class InstanceEntity : public IInstance<InstanceType>, public Entity
{
public:
	~InstanceEntity(void);
	InstanceEntity(D3DXVECTOR3 start, D3DXVECTOR2 size, float speed);

	InstanceType GetInstanceData();
};