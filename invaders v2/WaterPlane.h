#pragma once

#include "includes.h"
#include "WaterShader.h"
#include "Mirror.h"

template<class vt, class sh>
class WaterPlane : public Mirror<vt, sh>
{
	XMFLOAT4 reversePlane;
	RenderTarget refractionTarget;
public:
	WaterPlane(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, 
		int resWidth, int resHeight, float screenWidth, float screenHeight, ComPtr<ID3D11ShaderResourceView> normal);
	WaterPlane(Mirror &&other);

	void Render(const RenderParams &params);
	RenderTarget &GetRefractionTarget(){ return refractionTarget; }
	XMVECTOR GetReversePlane(){ return XMLoadFloat4(&reversePlane); }
	virtual void Init(ComPtr<ID3D11Device> device);
};

typedef WaterPlane<TextureVertexType, WaterShader> SimpleWaterPlane;

template<class vt, class sh>
WaterPlane<vt, sh>::WaterPlane(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel,
	sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight, ComPtr<ID3D11ShaderResourceView> normal)
:Mirror(screenPos, rot, screenModel, screenShader, resWidth, resHeight, screenWidth, screenHeight),
refractionTarget(resWidth, resHeight),
reversePlane(Utils::PlaneFromPointAndRot(screenPos, rot, true))
{
	textures.push_back(NULL);
	textures.push_back(normal);
}

template<class vt, class sh>
WaterPlane<vt, sh>::WaterPlane(Mirror &&other) :Mirror(move(other)),
reversePlane(move(other.reversePlane)), refractionTarget(move(other.refractionTarget))
{
}

template<class vt, class sh>
void WaterPlane<vt, sh>::Render(const RenderParams &params)
{
	textures[1] = refractionTarget.GetRenderedTexture();
	Mirror::Render(params);
}

template<class vt, class sh>
void WaterPlane<vt, sh>::Init(ComPtr<ID3D11Device> device)
{
	Mirror::Init(device);
	refractionTarget.Init(device);
}