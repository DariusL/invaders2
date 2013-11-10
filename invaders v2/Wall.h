#pragma once
#include "baseinstancer.h"
#include "InstanceEntity.h"
#include "ColorInstancedShader.h"
class Wall : public SimpleBaseInstancer
{
	vector<InstanceEntity> blocks;
	int width;
	int height;

	XMFLOAT3 topLeft;
	bool changed;
public:
	Wall(XMFLOAT3 center, int width, int height, ColorModel &model, ColorInstancedShader &shader);
	~Wall(void);
	bool Update(ComPtr<ID3D11DeviceContext>);

	void CollideWith(list<InstanceEntity> &bullets);
private:
	void CollideWith(InstanceEntity &bullet);
	InstanceEntity &GetBlock(int x, int y);
};
