#pragma once
#include "iinstance.h"
#include "Globals.h"
#include "Entity.h"

class InstanceEntity : public IInstance<InstanceType>, public Entity
{
public:
	InstanceEntity(void);
	~InstanceEntity(void);

	 InstanceType GetInstanceData();
};

