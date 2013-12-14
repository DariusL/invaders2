#pragma once

#include "Camera.h"
#include "CameraBall.h"
#include "DrawableTexturedEntity.h"

class RemoteCamera : public Camera, public IDrawable
{
	CameraBall cameraBall;
	ComVector<ID3D11ShaderResourceView> textures;
	DrawableTexturedEntity<TextureVertexType, TextureShader> screen;
public:
	RemoteCamera(XMFLOAT3 cameraPos, XMFLOAT3 cameraDir, XMFLOAT3 screenPos, XMFLOAT3 screenRot, TexturedModel &screenModel,
		TextureShader &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	RemoteCamera(RemoteCamera &&other);

	void Init(ComPtr<ID3D11Device> context);
	void Render(RenderParams &params);
	CameraBall &GetCameraBall(){ return cameraBall; }
};