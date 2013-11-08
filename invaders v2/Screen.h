#pragma once

#include "RenderTarget.h"
#include "DrawableTexturedEntity.h"

template<class vt, class sh>
class Screen : public IDrawable
{
	ComVector<ID3D11ShaderResourceView> renderTexture;
	RenderTarget renderTarget;
	DrawableTexturedEntity<vt, sh> screen;
public:
	Screen(D3DXVECTOR3 screenPos, D3DXVECTOR3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	Screen(Screen &&other);

	void Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
	RenderTarget &GetRenderTarget(){ return renderTarget; }
};

typedef Screen<TextureVertexType, TextureShader> SimpleScreen;

template<class vt, class sh>
Screen<vt, sh>::Screen(D3DXVECTOR3 screenPos, D3DXVECTOR3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight)
:renderTarget(resWidth, resHeight), screen(screenPos, rot, screenModel, screenShader, NULL, D3DXVECTOR3(screenWidth, screenHeight, 1.0f))
{
}

template<class vt, class sh>
Screen<vt, sh>::Screen(Screen &&other)
: renderTarget(move(other.renderTarget)), screen(move(other.screen))
{
}

template<class vt, class sh>
void Screen<vt, sh>::Init(ComPtr<ID3D11Device> device)
{
	renderTexture.push_back(NULL);
	renderTarget.Init(device);
	screen.Init(device);
}

template<class vt, class sh>
void Screen<vt, sh>::Render(const RenderParams &params)
{
	renderTexture[0] = renderTarget.GetRenderedTexture();
	screen.Render(params, renderTexture);
}