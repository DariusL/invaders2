#pragma once
#include "baseinstancer.h"
class Wall : public BaseInstancer
{
	vector<bool> blocks;
	int width;
	int height;

	D3DXVECTOR3 center;
	D3DXVECTOR2 blockSize;
	D3DXVECTOR3 topLeft;
	bool changed;
public:
	Wall(D3DXVECTOR3 center, int width, int height, shared_ptr<Model> model, D3DXVECTOR2 blockSize);
	~Wall(void);
	bool Update(ComPtr<ID3D11DeviceContext>);
};

