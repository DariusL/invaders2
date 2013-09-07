#pragma once
#pragma warning(disable : 4005)

#include <memory>
#include <list>

#include "IDrawableObject.h"
#include "Model.h"
#include "ColorInstancedShader.h"

using namespace std;
using namespace Microsoft::WRL;

class BaseInstancer : public IDrawableObject
{
public:
	BaseInstancer(shared_ptr<Model>, int maxObjectCount, int instanceSize);
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
	void Render(RenderParams);

private:
	bool InitBuffers(ComPtr<ID3D11Device>);
	void SetBuffers(ComPtr<ID3D11DeviceContext>);
	bool Update(ComPtr<ID3D11DeviceContext>);
};