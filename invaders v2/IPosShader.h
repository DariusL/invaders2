#pragma once

#include "IShader.h"

class IPositionShader : public IShader
{
public:
	IPositionShader(wstring vs, wstring ps):IShader(vs, ps){}
	virtual ~IPositionShader(){}

	virtual void SetShaderParameters(RenderParams &params, const XMMATRIX &world)
	{
		MatrixType vertexMatrices;
		
		XMStoreFloat4x4(&vertexMatrices.projection, XMMatrixTranspose(params.projection));
		XMStoreFloat4x4(&vertexMatrices.view, XMMatrixTranspose(params.view));
		XMStoreFloat4x4(&vertexMatrices.world, XMMatrixTranspose(world));
		Utils::CopyToBuffer(matrixBuffer.Get(), vertexMatrices, params.context);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

		SetShader(params);
	}
};