#pragma once

#include "Camera.h"
#include "Screen.h"

class RemoteCamera : public Camera, public SimpleScreen
{
public:
	RemoteCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraDir, D3DXVECTOR3 screenPos, D3DXVECTOR3 screenRot, TexturedModel &screenModel, TextureShader &screenShader,
		int resWidth, int resHeight, float screenWidth, float screenHeight);
	RemoteCamera(RemoteCamera &&other);
};