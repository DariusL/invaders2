#pragma once 

#include "IPosShader.h"

class IInstanceShader : public IPositionShader
{
	Buffer<InstancedMatrixType> matrixBuffer;
public:
	IInstanceShader(wstring vs, wstring ps) :IPositionShader(vs, ps){}
	virtual ~IInstanceShader(){}

	virtual void RenderShaderInstanced(ID3D11DeviceContext *context, int indexCount, int instanceCount)
	{ 
		context->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
	}

	virtual void RenderShader(ID3D11DeviceContext *context, int indexCount){ AssertBool(false, L"RenderShader called on an instanced shader"); }

	void SetShaderParameters(RenderParams &params, const XMMATRIX &posMatrix){ AssertBool(false, L"SetShaderParameters called on an instanced shader"); }

	virtual void SetShaderParametersInstanced(RenderParams &params)
	{
		InstancedMatrixType matrices;
		XMStoreFloat4x4(&matrices.view, XMMatrixTranspose(params.view));
		XMStoreFloat4x4(&matrices.projection, XMMatrixTranspose(params.projection));
		Utils::CopyToBuffer(matrixBuffer.Get(), matrices, params.context);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

		SetShader(params);
	}

	virtual void InitializeShaderBuffers(ID3D11Device *device)
	{
		matrixBuffer = Buffer<InstancedMatrixType>(device);
	}
};