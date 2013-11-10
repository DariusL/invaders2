#pragma once

#include "IShader.h"

class IPositionShader : public IShader
{
public:
	IPositionShader(wstring vs, wstring ps):IShader(vs, ps){}
	virtual ~IPositionShader(){}

	virtual void SetShaderParameters(const RenderParams &params, const XMMATRIX &world)
	{
		MatrixType vertexMatrices;
		
		XMStoreFloat4x4(&vertexMatrices.projection, XMMatrixTranspose(params.projection));
		XMStoreFloat4x4(&vertexMatrices.view, XMMatrixTranspose(params.view));
		XMStoreFloat4x4(&vertexMatrices.world, XMMatrixTranspose(world));
		Utils::CopyToBuffer(matrixBuffer, vertexMatrices, params.context);

		XMVECTOR clip = XMLoadFloat4(&params.clipPlane);

		XMMATRIX view = XMMatrixInverse(NULL, params.view);
		view = XMMatrixTranspose(view);
		XMMATRIX project = XMMatrixInverse(NULL, params.projection);
		project = XMMatrixTranspose(project);
		clip = XMPlaneTransform(clip, view);
		clip = XMPlaneTransform(clip, project);

		XMFLOAT4 vec;
		XMStoreFloat4(&vec, clip);
		Utils::CopyToBuffer(clipBuffer, vec, params.context);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
		params.context->VSSetConstantBuffers(1, 1, clipBuffer.GetAddressOf());

		params.context->IASetInputLayout(layout.Get());

		params.context->VSSetShader(vertexShader.Get(), NULL, 0);
		params.context->PSSetShader(pixelShader.Get(), NULL, 0);
	}
};