#pragma once
#include "BaseInstancer.h"
#include "Model.h"
class Instancer : public BaseInstancer<NormalVertexType, GlobalDiffuseShader, InstanceType>
{
public:
	Instancer(int objectCount);
	~Instancer();
};

