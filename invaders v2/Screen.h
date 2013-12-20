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
	int width, height;
public:
	Screen(ComPtr<ID3D11Device> device, XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	Screen(Screen &&other);
	Screen(Screen&) = delete;

	void Render(RenderParams &params);
	RenderTarget &GetRenderTarget(){ return renderTarget; }
	int GetTextureWidth(){ return width; }
	int GetTextureHeight(){ return height; }
};

typedef Screen<TextureVertexType, TextureShader> SimpleScreen;

template<class vt, class sh>
Screen<vt, sh>::Screen(ComPtr<ID3D11Device> device, XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight)
:renderTarget(resWidth, resHeight), screen(screenPos, rot, screenModel, screenShader, NULL, XMFLOAT3(screenWidth, screenHeight, 1.0f)),
width(resWidth), height(resHeight)
{
	textures.push_back(NULL);
	renderTarget.Init(device);
}

template<class vt, class sh>
Screen<vt, sh>::Screen(Screen &&other)
: renderTarget(move(other.renderTarget)), screen(move(other.screen)), textures(move(other.textures))
{
}

template<class vt, class sh>
void Screen<vt, sh>::Render(RenderParams &params)
{
	textures[0] = renderTarget.GetRenderedTexture();
	screen.Render(params, textures);
}