#pragma once
#include "idrawableobject.h"
#include "Entity.h"
#include "TexturedNormalModel.h"
#include "includes.h"
#include "NormalMappedShader.h"

class DrawableBumpyEntity : public IDrawableObject, public Entity
{
	shared_ptr<TexturedNormalModel> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<NormalMappedShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
	ComPtr<ID3D11ShaderResourceView> normalMap;
public:
	DrawableBumpyEntity(D3DXVECTOR3 pos, shared_ptr<TexturedNormalModel> model);
	~DrawableBumpyEntity(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &renderParams);
private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);
};

