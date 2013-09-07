#pragma once
#include "baseinstancer.h"
#include "InstanceShooter.h"
class ShooterListInstancer :
	public BaseInstancer
{
public:
	ShooterListInstancer(shared_ptr<Model> model, int maxInstanceCount);
	~ShooterListInstancer(void);

	void SetData(list<InstanceShooter> &instances);
};

