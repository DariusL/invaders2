#pragma once
#include "graphicsobject.h"
#include "ColorInstancedShader.h"
#include <memory>
#include <list>

using namespace std;

class BulletGraphics : public GraphicsObject
{
protected:
	static const int MAX_BULLET_COUNT = 100;

	int bulletCount;
	Model *model;
	unique_ptr<ColorInstancedShader> shader;
	unique_ptr<D3DXVECTOR3[]> bulletData;

	unique_ptr<unsigned int[]> offsets;
	unique_ptr<unsigned int[]> strides;

	ID3D11Buffer **vertexBuffers;
	ID3D11Buffer *indexBuffer;
public:
	BulletGraphics(void);
	~BulletGraphics(void);

	public:
	bool Init(ID3D11Device*, World*, HWND);
	void Render(ID3D11DeviceContext*, D3DXMATRIX);
	void SetModel(Model *model);

protected:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void SetBuffers(ID3D11DeviceContext*);
	virtual bool Update(ID3D11DeviceContext*);

};

