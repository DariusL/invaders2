#pragma once

#include "iinstance.h"
#include "Globals.h"
#include "Shooter.h"

class InstanceShooter : public Shooter, public IInstance<InstanceType>
{
public:
	InstanceShooter(D3DXVECTOR2 size, float speed, float fireRate);
	~InstanceShooter(void);

	InstanceType GetInstanceData();
};

