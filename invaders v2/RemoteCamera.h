#pragma once

#include "Camera.h"
#include "Screen.h"

class RemoteCamera : public Camera, public Screen
{
public:
	RemoteCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraDir, D3DXVECTOR3 screenPos, int width, int height, TexturedModel &screenModel, TextureShader &screenShader);
	RemoteCamera(RemoteCamera &&other);
};