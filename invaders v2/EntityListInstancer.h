#pragma once
#include "baseinstancer.h"
#include "InstanceEntity.h"
#include "ColorInstancedShader.h"

using namespace std;

class EntityListInstancer : public SimpleBaseInstancer
{
public:
	EntityListInstancer(ComPtr<ID3D11Device> device, ColorModel &model, ColorInstancedShader &shader, int maxInstanceCount);
	~EntityListInstancer(void);

	void SetData(list<InstanceEntity> &instances);
};