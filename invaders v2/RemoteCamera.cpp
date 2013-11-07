#include "includes.h"
#include "RemoteCamera.h"

RemoteCamera::RemoteCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraDir, D3DXVECTOR3 screenPos, int width, int height, TexturedModel &screenModel, TextureShader &screenShader)
:renderTarget(width, height), screen(screenPos, screenModel, screenShader)
{
	Move(cameraPos);
	Yaw(cameraDir.x);
	Pitch(cameraDir.y);
}

RemoteCamera::RemoteCamera(RemoteCamera &&other)
:Camera(move(other)), renderTarget(move(other.renderTarget)), screen(move(other.screen))
{
}

bool RemoteCamera::Init(ComPtr<ID3D11Device> device)
{
	renderTexture.push_back(NULL);
	renderTarget.Init(device);
	screen.Init(device);
	return true;
}

void RemoteCamera::Render(const RenderParams &params)
{
	renderTexture[0] = renderTarget.GetRenderedTexture();
	screen.Render(params, renderTexture);
}