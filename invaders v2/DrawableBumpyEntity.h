#pragma once

#include "DrawableEntity.h"
#include "NormalMappedShader.h"
#include "Model.h"
#include "Utils.h"

class DrawableBumpyEntity : public DrawableEntity<NormalMappedVertexType, NormalMappedShader>
{
	ComVector<ID3D11ShaderResourceView> normalMap;
public:
	DrawableBumpyEntity(XMFLOAT3 pos, NormalMappedModel &model, NormalMappedShader &shader, ComPtr<ID3D11ShaderResourceView> map)
		:DrawableEntity(pos, model, shader)
	{
		normalMap.push_back(map);
	}

	DrawableBumpyEntity(DrawableBumpyEntity &&other)
		:DrawableEntity(forward<DrawableBumpyEntity>(other))
	{
		normalMap = move(other.normalMap);
	}

	virtual void Render(RenderParams &renderParams)
	{
		if(!Update(renderParams.context))
			return;
		model.Set(renderParams.context);
		XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
		shader.SetShaderParametersTextured(renderParams, world, normalMap);
		shader.RenderShader(renderParams.context, model.GetIndexCount());
	}
};