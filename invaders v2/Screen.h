#pragma once

#include "RenderTarget.h"
#include "DrawableTexturedEntity.h"

class Screen : public IDrawable
{
	ComVector<ID3D11ShaderResourceView> renderTexture;
	RenderTarget renderTarget;
	SimpleTexturedEntity screen;
public:
	Screen(D3DXVECTOR3 screenPos, TexturedModel &screenModel, TextureShader &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	Screen(Screen &&other);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
	RenderTarget &GetRenderTarget(){ return renderTarget; }
};