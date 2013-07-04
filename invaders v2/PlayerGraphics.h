#pragma once
#include "graphicsobject.h"
#include "Model.h"
#include "ColorShader.h"

class PlayerGraphics : public GraphicsObject
{
public:
	bool Init(ID3D11Device*, World*, HWND);
	void Shutdown();
	void Render(ID3D11DeviceContext*, D3DXMATRIX);
	void SetModel(Model model);
	void SetPos(D3DXVECTOR3 pos);
	PlayerGraphics();

protected:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void SetBuffers(ID3D11DeviceContext*);
	void Update(ID3D11DeviceContext*);

private:
	Model model;
	D3DXVECTOR3 pos;
	D3DXMATRIX moveMatrix;
	ColorShader *shader;

	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
	ID3D11Buffer* matrixBuffer;
};

