#pragma once
#include "iposshader.h"
class GlobalDiffuseShader : public IPositionShader
{
public:
	GlobalDiffuseShader(void);
	~GlobalDiffuseShader(void);

public:
	bool Init(ComPtr<ID3D11Device> device);
	
	void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix);
	void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

private:
	bool InitializeShader(ComPtr<ID3D11Device> device, char* vsFilename, char* psFilename);

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11InputLayout> layout;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11Buffer> lightingBuffer;
};

