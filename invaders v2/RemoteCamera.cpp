#include "includes.h"
#include "RemoteCamera.h"

RemoteCamera::RemoteCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraDir, D3DXVECTOR3 screenPos, int width, int height, TexturedModel &screenModel, TextureShader &screenShader)
:Screen(screenPos, width, height, screenModel, screenShader)
{
	Move(cameraPos);
	Yaw(cameraDir.x);
	Pitch(cameraDir.y);
}

RemoteCamera::RemoteCamera(RemoteCamera &&other)
:Camera(move(other)), Screen(move(other))
{
}