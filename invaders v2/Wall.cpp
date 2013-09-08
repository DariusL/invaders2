#include "Wall.h"


Wall::Wall(D3DXVECTOR3 center, int width, int height, shared_ptr<Model> model) : BaseInstancer(model, width * height, sizeof(InstanceType))
{
	this->width = width;
	this->height = height;
	this->center = center;
	blocks = Utils::GetGrid(width, height, center, model->hitbox, model);
	blocks[0].Kill();
	blocks[width - 1].Kill();
	changed = true;

}


Wall::~Wall(void)
{
}

bool Wall::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(changed)
	{
		InstanceType instance;
		changed = false;
		instanceCount = 0;
		for(auto &b : blocks)
		{
			if(!b.IsDead())
			{
				memcpy(instanceData.get() + instanceCount * instanceSize, &b.GetInstanceData(), instanceSize);
				instanceCount++;
			}
		}

	}
	return BaseInstancer::Update(context);
}