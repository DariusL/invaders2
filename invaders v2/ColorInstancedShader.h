#pragma once

#pragma warning(disable : 4005)

#include "includes.h"

#include "Utils.h"
#include "IInstanceShader.h"

using namespace std;

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(void);
	~ColorInstancedShader(void);

	bool Init(ComPtr<ID3D11Device>);
	void SetShaderParameters(const RenderParams&);
	void RenderShader(ComPtr<ID3D11DeviceContext>, int indexCount, int instanceCount);

protected:
	bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
};