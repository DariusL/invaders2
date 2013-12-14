#pragma once 

#include "IPosShader.h"

class IInstanceShader : public IPositionShader
{
public:
	IInstanceShader(wstring vs, wstring ps) :IPositionShader(vs, ps){}
	virtual ~IInstanceShader(){}

	virtual void RenderShaderInstanced(ComPtr<ID3D11DeviceContext> context, int indexCount, int instanceCount)
	{ 
		context->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
	}

	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount){ AssertBool(false, L"RenderShader called on an instanced shader"); }

	void SetShaderParameters(RenderParams &params, const XMMATRIX &posMatrix){ AssertBool(false, L"SetShaderParameters called on an instanced shader"); }

	virtual void SetShaderParametersInstanced(RenderParams &params)
	{
		InstancedMatrixType matrices;
		XMStoreFloat4x4(&matrices.view, XMMatrixTranspose(params.view));
		XMStoreFloat4x4(&matrices.projection, XMMatrixTranspose(params.projection));
		Utils::CopyToBuffer(matrixBuffer, matrices, params.context);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

		SetShader(params);
	}

	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;

		// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(InstancedMatrixType);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;

		// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));
	}
};