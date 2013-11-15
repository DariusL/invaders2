#pragma once
#include "BaseInstancer.h"
#include "ColorInstancedShader.h"
#include "Model.h"
class Instancer : public BaseInstancer<NormalVertexType, ColorInstancedShader, InstanceType>
{
public:
	Instancer(int objectCount);
	~Instancer();
};

