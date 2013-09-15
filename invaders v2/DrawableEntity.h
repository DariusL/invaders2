#pragma once
#include "entity.h"
#include "IDrawableObject.h"
#include "GlobalDiffuseShader.h"

#include <memory>
#include "NormalModel.h"
class DrawableEntity : public Entity, public IDrawableObject
{
	shared_ptr<NormalModel> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<IPositionShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
	vector<int> shaderIndices;
	int currentShader;
public:
	DrawableEntity(D3DXVECTOR3 pos, shared_ptr<NormalModel> model);
	~DrawableEntity(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(RenderParams renderParams);
	void SwapShader();
private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);
};

