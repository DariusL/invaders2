#pragma once

#include "IShader.h"

class IPositionShader : public IShader
{
	Buffer<MatrixType> matrixBuffer;
public:
	IPositionShader(wstring vs, wstring ps):IShader(vs, ps){}
	virtual ~IPositionShader(){}

	virtual void InitializeShaderBuffers(ID3D11Device *device)
	{
		matrixBuffer = Buffer<MatrixType>(device);
	}

	virtual void SetShaderParameters(RenderParams &params, const XMMATRIX &world)
	{
		MatrixType vertexMatrices;
		
		XMStoreFloat4x4(&vertexMatrices.projection, XMMatrixTranspose(params.projection));
		XMStoreFloat4x4(&vertexMatrices.view, XMMatrixTranspose(params.view));
		XMStoreFloat4x4(&vertexMatrices.world, XMMatrixTranspose(world));
		matrixBuffer.SetData(params.context, vertexMatrices);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

		SetShader(params);
	}
};