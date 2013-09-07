#pragma once
#pragma warning(disable : 4005)
#include <memory>
#include <list>

#include "IDrawable.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "Entity.h"

using namespace std;
class Bullets : public IDrawable
{
public:
	Bullets(shared_ptr<Model> model);
	Bullets();
	~Bullets(void);

private:

	static const int MAX_BULLET_COUNT = 100;

	int bulletCount;
	shared_ptr<Model> model;

	shared_ptr<ColorInstancedShader> shader;
	unique_ptr<InstanceType[]> bulletData;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> instanceBuffer;
	BufferInfo instanceInfo;

	ComPtr<ID3D11Buffer> indexBuffer;

public:
	void setBullets(const list<Entity> &bullets);


	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);
	void SetModel(shared_ptr<Model> model);

private:
	bool InitBuffers(ComPtr<ID3D11Device>);
	void SetBuffers(ComPtr<ID3D11DeviceContext>);
	bool Update(ComPtr<ID3D11DeviceContext>);
};