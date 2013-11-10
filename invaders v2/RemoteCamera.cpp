#include "includes.h"
#include "RemoteCamera.h"

RemoteCamera::RemoteCamera(XMFLOAT3 cameraPos, XMFLOAT3 cameraDir, XMFLOAT3 screenPos, XMFLOAT3 screenRot, TexturedModel &screenModel, TextureShader &screenShader,
	int resWidth, int resHeight, float screenWidth, float screenHeight)
:Screen(screenPos, screenRot, screenModel, screenShader, resWidth, resHeight, screenWidth, screenHeight)
{
	Move(cameraPos);
	Yaw(cameraDir.x);
	Pitch(cameraDir.y);
	Roll(cameraDir.z);
}

RemoteCamera::RemoteCamera(RemoteCamera &&other)
:Camera(move(other)), Screen(move(other))
{
}