#include "includes.h"
#include "RemoteCamera.h"

RemoteCamera::RemoteCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraDir, D3DXVECTOR3 screenPos, TexturedModel &screenModel, TextureShader &screenShader, 
	int resWidth, int resHeight, float screenWidth, float screenHeight)
:Screen(screenPos, screenModel, screenShader, resWidth, resHeight, screenWidth, screenHeight)
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