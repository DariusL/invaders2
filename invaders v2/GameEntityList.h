#pragma once
#include "includes.h"
#include "BaseInstancer.h"
#include "GameEntity.h"
#include "ColorInstancedShader.h"
#include "Model.h"

class GameEntityList : public BaseInstancer<VertexType, ColorInstancedShader, e::XMFLOAT3>
{
protected:
	e::vector<e::shared_ptr<GameEntity>> enemies;
public:
	GameEntityList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount);
	GameEntityList(GameEntityList &&other);

	bool Update(ID3D11DeviceContext *context);
	virtual void Loop(int frame);
	void Add(e::shared_ptr<GameEntity> enemy);
	void MoveBy(e::XMVECTOR pos);
protected:
	virtual void OnRemove(const e::shared_ptr<GameEntity> entity){}
};