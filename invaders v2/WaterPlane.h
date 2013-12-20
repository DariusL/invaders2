#pragma once

#include "includes.h"
#include "WaterShader.h"
#include "Mirror.h"

template<class vt, class sh>
class WaterPlane : public Mirror<vt, sh>
{
	XMFLOAT4 reversePlane;
	MirrorBall refractionBall;
public:
	WaterPlane(ComPtr<ID3D11Device> device, XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader,
		int resWidth, int resHeight, float screenWidth, float screenHeight, ComPtr<ID3D11ShaderResourceView> normal);
	WaterPlane(Mirror &&other);

	void Render(RenderParams &params);
	XMVECTOR GetReversePlane(){ return XMLoadFloat4(&reversePlane); }

	MirrorBall &GetRefractionBall(){ return refractionBall; }
};

typedef WaterPlane<TextureVertexType, WaterShader> SimpleWaterPlane;

template<class vt, class sh>
WaterPlane<vt, sh>::WaterPlane(ComPtr<ID3D11Device> device, XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel,
	sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight, ComPtr<ID3D11ShaderResourceView> normal)
:Mirror(device, screenPos, rot, screenModel, screenShader, resWidth, resHeight, screenWidth, screenHeight),
refractionBall(resWidth, resHeight, ([this](RenderParams &params) -> void
{
	params.view = params.camera->GetViewMatrix();
	XMStoreFloat4(&params.clipPlane, GetReversePlane());
})),
reversePlane(Utils::PlaneFromPointAndRot(screenPos, rot, true))
{
	textures.push_back(nullptr);
	textures.push_back(normal);

	refractionBall.Init(device);
}

template<class vt, class sh>
WaterPlane<vt, sh>::WaterPlane(Mirror &&other) :Mirror(move(other)),
reversePlane(move(other.reversePlane)), refractionBall(move(other.refractionBall))
{
}

template<class vt, class sh>
void WaterPlane<vt, sh>::Render(RenderParams &params)
{
	textures[1] = refractionBall.GetCurrentTexture();
	Mirror::Render(params);
}