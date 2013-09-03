#pragma once
#pragma warning(disable : 4005)
#include "idrawable.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "Entity.h"
#include <memory>
#include <list>

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
	unique_ptr<ColorInstancedShader> shader;
	unique_ptr<D3DXVECTOR3[]> bulletData;

	unique_ptr<unsigned int[]> offsets;
	unique_ptr<unsigned int[]> strides;

	ID3D11Buffer **vertexBuffers;
	ID3D11Buffer *indexBuffer;

public:
	void setBullets(const list<Entity> &bullets);


	bool Init(ID3D11Device*, HWND);
	void Render(RenderParams);
	void SetModel(shared_ptr<Model> model);

private:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void SetBuffers(ID3D11DeviceContext*);
	bool Update(ID3D11DeviceContext*);
};