#pragma once

#include "entity.h"
#include "IDrawableObject.h"
#include "GlobalDiffuseShader.h"
#include "models.h"
#include "includes.h"
class WaterPlane : public Entity, public IDrawableObject
{
	shared_ptr<TexturedModel> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<IPositionShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
public:
	WaterPlane(D3DXVECTOR3 pos, shared_ptr<TexturedModel> model);
	~WaterPlane(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &renderParams);
	void SetTextures(const vector<ComPtr<ID3D11ShaderResourceView>> textures);
private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);
};

