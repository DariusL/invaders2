#include "includes.h"
#include "RemoteCamera.h"

RemoteCamera::RemoteCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraDir, D3DXVECTOR3 screenPos, TexturedModel &screenModel, TextureShader &screenShader, int width, int height)
:Screen(screenPos, screenModel, screenShader, width, height)
{
	Move(cameraPos);
	Yaw(cameraDir.x);
	Pitch(cameraDir.y);
}

RemoteCamera::RemoteCamera(RemoteCamera &&other)
:Camera(move(other)), Screen(move(other))
{
}