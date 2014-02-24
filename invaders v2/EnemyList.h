#pragma once
#include "includes.h"
#include "BaseInstancer.h"
#include "ShooterEntity.h"

class EnemyList : public BaseInstancer<VertexType, ColorInstancedShader, e::XMFLOAT3>
{
	vector<ShooterEntity> enemies;
public:
	EnemyList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount)
		:BaseInstancer(device, model, shader, maxObjectCount){}
	EnemyList(EnemyList &&other)
		:BaseInstancer(move(other)){ swap(enemies, other.enemies); }

	bool Update(ID3D11DeviceContext *context);

	void Add(ShooterEntity &&enemy);
};