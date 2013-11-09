#pragma once

#include "IShader.h"

class IPositionShader : public IShader
{
public:
	IPositionShader(wstring vs, wstring ps):IShader(vs, ps){}
	virtual ~IPositionShader(){}

	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix)
	{
		MatrixType vertexMatrices;

		D3DXMatrixTranspose(&vertexMatrices.projection, &params.projection);
		D3DXMatrixTranspose(&vertexMatrices.view, &params.view);
		D3DXMatrixTranspose(&vertexMatrices.world, &posMatrix);
		Utils::CopyToBuffer(matrixBuffer, vertexMatrices, params.context);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

		params.context->IASetInputLayout(layout.Get());

		params.context->VSSetShader(vertexShader.Get(), NULL, 0);
		params.context->PSSetShader(pixelShader.Get(), NULL, 0);
	}
};