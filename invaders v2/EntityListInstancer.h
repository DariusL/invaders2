#pragma once
#pragma warning(disable : 4005)
#include "baseinstancer.h"
#include "InstanceEntity.h"


using namespace std;

class EntityListInstancer : public BaseInstancer
{
public:
	EntityListInstancer(shared_ptr<Model> model, int maxInstanceCount);
	~EntityListInstancer(void);

	void SetData(list<InstanceEntity> &instances);
};