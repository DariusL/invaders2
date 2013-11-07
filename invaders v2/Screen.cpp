#include "includes.h"
#include "Screen.h"

Screen::Screen(D3DXVECTOR3 screenPos, TexturedModel &screenModel, TextureShader &screenShader, int width, int height)
:renderTarget(width, height), screen(screenPos, screenModel, screenShader, NULL, D3DXVECTOR3((float)width, (float)height, 0.0f))
{
}

Screen::Screen(Screen &&other)
:renderTarget(move(other.renderTarget)), screen(move(other.screen))
{
}

bool Screen::Init(ComPtr<ID3D11Device> device)
{
	renderTexture.push_back(NULL);
	renderTarget.Init(device);
	screen.Init(device);
	return true;
}

void Screen::Render(const RenderParams &params)
{
 	renderTexture[0] = renderTarget.GetRenderedTexture();
	screen.Render(params, renderTexture);
}