#include "includes.h"
#include "BulletList.h"
#include "Observers.h"

BulletList::BulletList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMFLOAT2 dir, int spawnEvent)
:GameEntityList(device, model, shader, maxObjectCount), dir(dir)
{
	or = GameObservers::Register(spawnEvent, e::bind(&BulletList::Add, this, e::placeholders::_1));
}

void BulletList::Loop(int frame)
{
	using namespace e;
	GameEntityList::Loop(frame);
	auto dir = e::XMLoadFloat2(&this->dir);
	for (auto &enemy : enemies)
	{
		auto vec = dir * (enemy->GetSpeed() * frame);
		enemy->MoveBy(vec);
	}
}

void BulletList::Render(RenderParams &params)
{
	InstanceType it;
	instanceCount = enemies.size();
	instanceData.clear();
	for (auto &enemy : enemies)
	{
		it.color = Red;
		it.position = enemy->GetPos();
		instanceData.push_back(it);
	}

	if (!Update(params.context))
		return;
	model.Set(params.context);
	params.context->IASetVertexBuffers(1, 1, instanceBuffer.GetAddressOf(), instanceBuffer.GetStride(), instanceBuffer.GetOffset());
	shader.SetShaderParametersInstanced(params);
	shader.RenderShaderInstanced(params.context, model.GetIndexCount(), instanceCount);
}