#pragma once
#pragma warning(disable : 4005)
#include "baseinstancer.h"
#include "InstanceEntity.h"
#include "ColorInstancedShader.h"

using namespace std;

class EntityListInstancer : public SimpleBaseInstancer
{
public:
	EntityListInstancer(shared_ptr<ColorModel> model, shared_ptr<ColorInstancedShader> shader, int maxInstanceCount);
	~EntityListInstancer(void);

	void SetData(list<InstanceEntity> &instances);
};