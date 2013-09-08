#pragma once
#include "baseinstancer.h"
#include "InstanceEntity.h"
class Wall : public BaseInstancer
{
	vector<InstanceEntity> blocks;
	int width;
	int height;

	D3DXVECTOR3 center;
	D3DXVECTOR3 topLeft;
	bool changed;
public:
	Wall(D3DXVECTOR3 center, int width, int height, shared_ptr<Model> model);
	~Wall(void);
	bool Update(ComPtr<ID3D11DeviceContext>);
};

