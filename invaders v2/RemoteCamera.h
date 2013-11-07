#pragma once

#include "Camera.h"
#include "RenderTarget.h"
#include "DrawableTexturedEntity.h"

class RemoteCamera : public Camera, public IDrawable
{
	ComVector<ID3D11ShaderResourceView> renderTexture;
public:
	RenderTarget renderTarget;
	SimpleTexturedEntity screen;
	RemoteCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraDir, D3DXVECTOR3 screenPos, int width, int height, TexturedModel &screenModel, TextureShader &screenShader);
	RemoteCamera(RemoteCamera &&other);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
	RenderTarget &GetRenderTarget(){ return renderTarget; }
};