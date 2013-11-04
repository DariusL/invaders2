#pragma once

#include "DrawableEntity.h"
#include "NormalMappedShader.h"
#include "Models.h"

class DrawableBumpyEntity : public DrawableEntity<NormalMappedVertexType, NormalMappedShader>
{
	ComPtr<ID3D11ShaderResourceView> normalMap;
public:
	DrawableBumpyEntity(D3DXVECTOR3 pos, shared_ptr<Model<NormalMappedVertexType>> model, shared_ptr<NormalMappedShader> shader)
		:DrawableEntity(pos, model, shader){}

	virtual void Render(const RenderParams &renderParams)
	{
		if(!Update(renderParams.context))
			return;
		SetBuffers(renderParams.context);
		shader->SetShaderParameters(renderParams, moveMatrix, normalMap);
		shader->RenderShader(renderParams.context, model->indices.size());
	}

	virtual bool Init(ComPtr<ID3D11Device> device)
	{
		DrawableEntity::Init(device);

		Assert(D3DX11CreateShaderResourceViewFromFile(device.Get(), L"stage7.dds", NULL, NULL, &normalMap, NULL));

		return true;
	}
};