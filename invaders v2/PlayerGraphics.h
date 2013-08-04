#pragma once
#include "graphicsobject.h"
#include "Model.h"
#include "ColorShader.h"

class PlayerGraphics : public GraphicsObject
{
public:
	virtual bool Init(ID3D11Device*, World*, HWND);
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX);
	virtual void SetModel(Model *model);
	PlayerGraphics();
	~PlayerGraphics();

protected:
	virtual bool InitBuffers(ID3D11Device*);
	virtual void ShutdownBuffers();
	virtual void SetBuffers(ID3D11DeviceContext*);
	virtual bool Update(ID3D11DeviceContext*);

protected:
	Model *model;
	D3DXVECTOR3 pos;
	D3DXMATRIX moveMatrix;
	ColorShader *shader;

	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
	ID3D11Buffer* matrixBuffer;
};

