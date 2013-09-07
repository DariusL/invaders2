#include "Wall.h"


Wall::Wall(D3DXVECTOR3 center, int width, int height, shared_ptr<Model> model, D3DXVECTOR2 blockSize) : BaseInstancer(model, width * height, sizeof(InstanceType))
{
	this->width = width;
	this->height = height;
	this->blockSize = blockSize;
	this->center = center;
	for(int i = 0; i < width * height; i++)
	{
		blocks.push_back(true);
	}
	blocks[0] = false;
	blocks[width - 1] = false;
	changed = true;

	D3DXVECTOR2 betweenCenters = D3DXVECTOR2(
		(width - 1) * blockSize.x,
		(height - 1) * blockSize.y);
	topLeft = D3DXVECTOR3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);
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
		for(int i = 0; i < width * height; i++)
		{
			if(blocks[i])
			{
				int x = i % width;
				int y = i / width;
				instance.position = D3DXVECTOR3(x * blockSize.x, y * -blockSize.y, 0) + topLeft;
				memcpy(instanceData.get() + instanceCount * instanceSize, &instance, instanceSize);
				instanceCount++;
			}
		}

	}
	return BaseInstancer::Update(context);
}