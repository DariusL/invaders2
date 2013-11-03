#pragma once
#include "entity.h"
#include "IDrawableObject.h"
#include "Models.h"
#include "IPosShader.h"
#include "Globals.h"
using namespace std;
using namespace Microsoft::WRL;

class Light : public Entity, public IDrawableObject
{
	D3DXVECTOR4 color;
	shared_ptr<ColorModel> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<IPositionShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
public:
	Light(D3DXVECTOR3 pos, D3DXVECTOR4 color);
	~Light(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &renderParams);
	D3DXVECTOR3 GetPos();

	const D3DXVECTOR4 &GetColor(){return color;}
private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);

};