#pragma once

#include "DrawableEntity.h"
#include "NormalMappedShader.h"
#include "Model.h"

class DrawableBumpyEntity : public DrawableEntity<NormalMappedVertexType, NormalMappedShader>
{
	ComPtr<ID3D11ShaderResourceView> normalMap;
public:
	DrawableBumpyEntity(D3DXVECTOR3 pos, NormalMappedModel &model, NormalMappedShader &shader)
		:DrawableEntity(pos, model, shader){}

	DrawableBumpyEntity(DrawableBumpyEntity &&other)
		:DrawableEntity(forward<DrawableBumpyEntity>(other))
	{
		normalMap = move(other.normalMap);
	}

	virtual void Render(const RenderParams &renderParams)
	{
		if(!Update(renderParams.context))
			return;
		SetBuffers(renderParams.context);
		shader.SetShaderParametersTextured(renderParams, moveMatrix, normalMap);
		shader.RenderShader(renderParams.context, model.indices.size());
	}

	virtual void Init(ComPtr<ID3D11Device> device)
	{
		DrawableEntity::Init(device);

		Assert(D3DX11CreateShaderResourceViewFromFile(device.Get(), L"stage7.dds", NULL, NULL, &normalMap, NULL));
	}
};