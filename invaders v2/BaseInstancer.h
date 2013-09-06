#pragma once
#pragma warning(disable : 4005)
#include "idrawableobject.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "Entity.h"

#include <memory>
#include <list>
using namespace std;
using namespace Microsoft::WRL;

template<class Data>
class BaseInstancer : public IDrawableObject
{
public:
	BaseInstancer(shared_ptr<Model>, int maxObjectCount);
	~BaseInstancer(void);

protected:
	int maxInstanceCount;
	int instanceCount;

	shared_ptr<Model> model;

	shared_ptr<ColorInstancedShader> shader;
	unique_ptr<Data[]> bulletData;

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