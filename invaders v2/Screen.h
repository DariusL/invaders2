#pragma once

#include "RenderTarget.h"
#include "DrawableTexturedEntity.h"

template<class vt, class sh>
class Screen : public IDrawable
{
protected:
	ComVector<ID3D11ShaderResourceView> textures;
	RenderTarget renderTarget;
	DrawableTexturedEntity<vt, sh> screen;
public:
	Screen(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	Screen(Screen &&other);

	virtual void Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
	RenderTarget &GetRenderTarget(){ return renderTarget; }
};

typedef Screen<TextureVertexType, TextureShader> SimpleScreen;

template<class vt, class sh>
Screen<vt, sh>::Screen(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight)
:renderTarget(resWidth, resHeight), screen(screenPos, rot, screenModel, screenShader, NULL, XMFLOAT3(screenWidth, screenHeight, 1.0f))
{
	textures.push_back(NULL);
}

template<class vt, class sh>
Screen<vt, sh>::Screen(Screen &&other)
: renderTarget(move(other.renderTarget)), screen(move(other.screen)), textures(move(other.textures))
{
}

template<class vt, class sh>
void Screen<vt, sh>::Init(ComPtr<ID3D11Device> device)
{
	renderTarget.Init(device);
	screen.Init(device);
}

template<class vt, class sh>
void Screen<vt, sh>::Render(const RenderParams &params)
{
	textures[0] = renderTarget.GetRenderedTexture();
	screen.Render(params, textures);
}