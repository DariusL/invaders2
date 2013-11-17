#pragma once
#include "BaseInstancer.h"
class Instancer : public SimpleBaseInstancer
{
	vector<Entity> objects;
public:
	Instancer(int objectCount);
	~Instancer();

	bool Update(ComPtr<ID3D11DeviceContext> context);
};