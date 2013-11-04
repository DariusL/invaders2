#pragma once
#pragma warning(disable : 4005)
#include "baseinstancer.h"
#include "InstanceEntity.h"
#include "ColorInstancedShader.h"
class Wall : public SimpleBaseInstancer
{
	vector<InstanceEntity> blocks;
	int width;
	int height;

	D3DXVECTOR3 topLeft;
	bool changed;
public:
	Wall(D3DXVECTOR3 center, int width, int height, shared_ptr<ColorModel> model, shared_ptr<ColorInstancedShader> shader);
	~Wall(void);
	bool Update(ComPtr<ID3D11DeviceContext>);

	void CollideWith(list<InstanceEntity> &bullets);
private:
	void CollideWith(InstanceEntity &bullet);
	InstanceEntity &GetBlock(int x, int y);
};
