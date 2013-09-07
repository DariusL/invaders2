#pragma once
#include "baseinstancer.h"
#include "InstanceEntity.h"

#include <memory>
#include <list>

using namespace std;

class EntityListInstancer : public BaseInstancer
{
public:
	EntityListInstancer(shared_ptr<Model> model, int maxInstanceCount);
	~EntityListInstancer(void);

	void SetData(list<InstanceEntity> &instances);
};