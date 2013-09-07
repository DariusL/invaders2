#include "InstanceShooter.h"


InstanceShooter::InstanceShooter(D3DXVECTOR2 size, float speed, float fireRate) : Shooter(size, speed, fireRate)
{
}


InstanceShooter::~InstanceShooter(void)
{
}

InstanceType InstanceShooter::GetInstanceData()
{
	InstanceType ret;
	ret.position = pos;
	return ret;
}