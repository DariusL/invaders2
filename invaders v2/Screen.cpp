#include "includes.h"
#include "Screen.h"

Screen::Screen(D3DXVECTOR3 screenPos, TexturedModel &screenModel, TextureShader &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight)
:renderTarget(resWidth, resHeight), screen(screenPos, screenModel, screenShader, NULL, D3DXVECTOR3(screenWidth, screenHeight, 1.0f))
{
}

Screen::Screen(Screen &&other)
:renderTarget(move(other.renderTarget)), screen(move(other.screen))
{
}

void Screen::Init(ComPtr<ID3D11Device> device)
{
	renderTexture.push_back(NULL);
	renderTarget.Init(device);
	screen.Init(device);
}

void Screen::Render(const RenderParams &params)
{
 	renderTexture[0] = renderTarget.GetRenderedTexture();
	screen.Render(params, renderTexture);
}