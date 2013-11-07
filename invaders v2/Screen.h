#pragma once

#include "RenderTarget.h"
#include "DrawableTexturedEntity.h"

class Screen : public IDrawable
{
	ComVector<ID3D11ShaderResourceView> renderTexture;
	RenderTarget renderTarget;
	SimpleTexturedEntity screen;
public:
	Screen(D3DXVECTOR3 screenPos, int width, int height, TexturedModel &screenModel, TextureShader &screenShader);
	Screen(Screen &&other);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
	RenderTarget &GetRenderTarget(){ return renderTarget; }
};