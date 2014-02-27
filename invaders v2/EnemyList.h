#pragma once
#include "includes.h"
#include "BaseInstancer.h"
#include "ShooterEntity.h"
#include "ColorInstancedShader.h"
#include "Model.h"

class EnemyList : public BaseInstancer<VertexType, ColorInstancedShader, e::XMFLOAT3>
{
	vector<ShooterEntity> enemies;
	e::XMFLOAT3 pos;
public:
	EnemyList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMVECTOR pos);
	EnemyList(EnemyList &&other)
		:BaseInstancer(move(other)){ swap(enemies, other.enemies); }

	bool Update(ID3D11DeviceContext *context);

	void Add(ShooterEntity &&enemy);
	void MoveTo(e::XMVECTOR pos);
};