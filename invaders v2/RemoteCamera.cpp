#include "includes.h"
#include "RemoteCamera.h"

RemoteCamera::RemoteCamera(ComPtr<ID3D11Device> device, XMFLOAT3 cameraPos, XMFLOAT3 cameraDir, XMFLOAT3 screenPos, XMFLOAT3 screenRot, TexturedModel &screenModel, TextureShader &screenShader,
	int resWidth, int resHeight, float screenWidth, float screenHeight)
	:screen(screenPos, screenRot, screenModel, screenShader, nullptr, XMFLOAT3(screenWidth, screenHeight, 1.0f)),
	cameraBall(resWidth, resHeight, [this](RenderParams &params, Direct3D &direct3D)
{
	params.view = GetViewMatrix();
	params.pass = PASS_TYPE_NORMAL;
	params.projection = direct3D.GetProjectionMatrix();
	params.clipPlane = ZeroVec4;
})
{
	Move(cameraPos);
	Yaw(cameraDir.x);
	Pitch(cameraDir.y);
	Roll(cameraDir.z);
	textures.push_back(nullptr);

	cameraBall.Init(device);
}

RemoteCamera::RemoteCamera(RemoteCamera &&other)
:Camera(move(other)), screen(move(other.screen)), cameraBall(move(other.cameraBall)), textures(move(other.textures))
{
}

void RemoteCamera::Render(RenderParams &params)
{
	textures[0] = cameraBall.GetCurrentTexture();
	screen.Render(params, textures);
}