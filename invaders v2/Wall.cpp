#include "includes.h"
#include "Wall.h"


Wall::Wall(ID3D11Device *device, XMFLOAT3 center, int width, int height, ColorModel &model, ColorInstancedShader &shader) :
	SimpleBaseInstancer(device, model, shader, width * height, center)
{
	AssertBool(false, L"Wall got deimplemented");
	/*SetSize(XMFLOAT2(model.hitbox.x * width, model.hitbox.y * height));
	this->width = width;
	this->height = height;
	XMFLOAT2 betweenCenters = XMFLOAT2(
		(width - 1) * model.hitbox.x,
		(height - 1) * model.hitbox.y);
	this->topLeft = XMFLOAT3(center.x - betweenCenters.x / 2.0f, center.y + betweenCenters.y / 2.0f, 0);
	blocks = Utils::GetGrid(width, height, center, model.hitbox, model);
	blocks[0].Kill();
	blocks[width - 1].Kill();
	changed = true;*/
}


Wall::~Wall(void)
{
}

bool Wall::Update(ID3D11DeviceContext *context)
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
				instanceData[instanceCount] = b.GetInstanceData();
				instanceCount++;
			}
		}

	}
	return BaseInstancer::Update(context);
}

void Wall::CollideWith(list<InstanceEntity> &bullets)
{
	for(auto &b : bullets)
		CollideWith(b);
}

void Wall::CollideWith(InstanceEntity &bullet)
{
	/*if(!Entity::CollideWith(bullet))
		return;
	float column;
	int column2;
	float x = (bullet.GetPos().x - topLeft.x) / model.hitbox.x;
	float offset = Utils::Trunc(x, column);
	if(Utils::Trunc(x, column) > 0)
		column2 = (int)column + 1;
	else
		column2 = (int)column - 1;
	if(column2 >= width)
		column2 = -1;
	if(column >= width)
		column = -1;
	for(int i = height - 1; i >= 0; i--)
	{
		if(column >= 0)
		{
			if(GetBlock((int)column, i).CollideWithAndKillBoth(bullet))
			{
				changed = true;
				return;
			}
		}
		if(column2 >= 0)
			if(GetBlock(column2, i).CollideWithAndKillBoth(bullet))
			{
				changed = true;
				return;
			}
	}*/
}

InstanceEntity &Wall::GetBlock(int x, int y)
{
	return blocks[x + y * width];
}