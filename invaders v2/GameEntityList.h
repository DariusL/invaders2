#pragma once
#include "includes.h"
#include "BaseInstancer.h"
#include "GameEntity.h"
#include "ColorInstancedShader.h"
#include "Model.h"

class GameEntityList : public BaseInstancer<VertexType, ColorInstancedShader, InstanceType>
{
protected:
	e::vector<e::shared_ptr<GameEntity>> enemies;
public:
	GameEntityList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, float scale = 1.0f);
	GameEntityList(GameEntityList &&other);

	virtual void Loop(int frame);
	void Add(e::shared_ptr<GameEntity> enemy);
	void MoveBy(e::XMVECTOR pos);
	e::shared_ptr<GameEntity> Get(uint i);
	virtual void Render(RenderParams &params);
protected:
	virtual void OnRemove(const e::shared_ptr<GameEntity> entity){}
};