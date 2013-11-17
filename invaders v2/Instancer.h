#pragma once
#include "BaseInstancer.h"
class Instancer : public SimpleBaseInstancer
{
	vector<Entity> objects;
public:
	Instancer(int objectCount, float radius);
	virtual ~Instancer();

	virtual bool Update(ComPtr<ID3D11DeviceContext> context);
};