#pragma once
#pragma warning(disable : 4005)
#include "IDrawableObject.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "includes.h"

using namespace std;
using namespace Microsoft::WRL;

class BaseInstancer : public IDrawableObject
{
public:
	BaseInstancer(shared_ptr<Model> model, int maxObjectCount, int instanceSize);
	virtual ~BaseInstancer(void);

protected:
	int maxInstanceCount;
	int instanceCount;
	int instanceSize;

	shared_ptr<Model> model;

	shared_ptr<ColorInstancedShader> shader;
	unique_ptr<byte[]> instanceData;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> instanceBuffer;
	BufferInfo instanceInfo;

	ComPtr<ID3D11Buffer> indexBuffer;

public:
	bool Init(ComPtr<ID3D11Device>);
	void Render(const RenderParams&);

protected:
	bool InitBuffers(ComPtr<ID3D11Device>);
	void SetBuffers(ComPtr<ID3D11DeviceContext>);
	virtual bool Update(ComPtr<ID3D11DeviceContext>);
};