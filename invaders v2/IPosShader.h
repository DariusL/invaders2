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

		D3DXPLANE clip = params.clipPlane;
		if (clip != ZeroPlane)
		{
			D3DXMATRIX view, project;
			D3DXMatrixInverse(&view, NULL, &params.view);
			D3DXMatrixTranspose(&view, &view);
			D3DXMatrixInverse(&project, NULL, &params.projection);
			D3DXMatrixTranspose(&project, &project);
			D3DXPlaneTransform(&clip, &clip, &view);
			D3DXPlaneTransform(&clip, &clip, &project);
		}

		Utils::CopyToBuffer(clipBuffer, clip, params.context);

		params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
		params.context->VSSetConstantBuffers(1, 1, clipBuffer.GetAddressOf());

		params.context->IASetInputLayout(layout.Get());

		params.context->VSSetShader(vertexShader.Get(), NULL, 0);
		params.context->PSSetShader(pixelShader.Get(), NULL, 0);
	}
};