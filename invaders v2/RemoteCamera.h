#pragma once

#include "Camera.h"
#include "Screen.h"

class RemoteCamera : public Camera, public SimpleScreen
{
public:
	RemoteCamera(XMFLOAT3 cameraPos, XMFLOAT3 cameraDir, XMFLOAT3 screenPos, XMFLOAT3 screenRot, TexturedModel &screenModel,
		TextureShader &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	RemoteCamera(RemoteCamera &&other);
};