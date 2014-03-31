#pragma once
#include "includes.h"
#include "BaseInstancer.h"
#include "GameEntity.h"
#include "ColorInstancedShader.h"
#include "Model.h"

class GameEntityList : public BaseInstancer<VertexType, ColorInstancedShader, e::XMFLOAT3>
{
private:
	e::XMFLOAT4 color;
protected:
	e::vector<e::shared_ptr<GameEntity>> enemies;
public:
	GameEntityList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMFLOAT4 color = e::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	GameEntityList(GameEntityList &&other);

	bool Update(ID3D11DeviceContext *context);
	virtual void Loop(int frame);
	void Add(e::shared_ptr<GameEntity> enemy);
	void MoveBy(e::XMVECTOR pos);
	e::shared_ptr<GameEntity> Get(uint i);
	void Render(const RenderParams &params);
protected:
	virtual void OnRemove(const e::shared_ptr<GameEntity> entity){}
};