#pragma once

#include "IShader.h"

class IPositionShader : public IShader
{
	struct MatrixType
	{
		e::XMFLOAT4X4 world;
		e::XMFLOAT4X4 view;
		e::XMFLOAT4X4 projection;
	};
	Buffer<MatrixType> matrixBuffer;
public:
	IPositionShader(e::wstring vs, e::wstring ps) :IShader(vs, ps){}
	virtual ~IPositionShader(){}

	virtual void SetShaderParameters(const RenderParams &params, const e::XMMATRIX &world)
	{
		MatrixType vertexMatrices;
		
		XMStoreFloat4x4(&vertexMatrices.projection, XMMatrixTranspose(params.projection));
		XMStoreFloat4x4(&vertexMatrices.view, XMMatrixTranspose(params.view));
		XMStoreFloat4x4(&vertexMatrices.world, XMMatrixTranspose(world));
		matrixBuffer.SetData(params.context, vertexMatrices);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

		SetShader(params);
	}
protected:
	virtual void InitializeShaderBuffers(ID3D11Device *device)
	{
		matrixBuffer = Buffer<MatrixType>(device);
	}
};