#pragma once

#include "entity.h"
#include "IDrawableObject.h"
#include "GlobalDiffuseShader.h"
#include "models.h"
#include "includes.h"
#include "WaterShader.h"
#include "RenderTarget.h"
class WaterPlane : public Entity, public IDrawableObject
{
	shared_ptr<TexturedModel> model;
	D3DXMATRIX moveMatrix;
	WaterShader &shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;

	vector<ComPtr<ID3D11ShaderResourceView>> textures;
	ComPtr<ID3D11ShaderResourceView> nullResource;

	shared_ptr<RenderTarget> renderTarget;
public:
	WaterPlane(D3DXVECTOR3 pos, shared_ptr<TexturedModel> model, WaterShader &shader);
	~WaterPlane(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &renderParams);
	shared_ptr<RenderTarget> GetRenderTarget(){return renderTarget;}
private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);
};