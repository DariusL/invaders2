#pragma once

#include "Screen.h"
#include "Utils.h"
#include "MirrorShader.h"
#include "MirrorBall.h"

template<class vt, class sh>
class Mirror : public IDrawable
{
protected:
	XMFLOAT4 mirrorPlane;
	XMFLOAT4 zeroPlane;
	MirrorBall reflectionBall;

	ComVector<ID3D11ShaderResourceView> textures;
	DrawableTexturedEntity<vt, sh> screen;
public:
	Mirror(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	Mirror(Mirror&) = delete;
	Mirror(Mirror&&);

	XMVECTOR GetMirrorPlane(){ return XMLoadFloat4(&mirrorPlane); }
	XMVECTOR GetZeroPlane(){ return XMLoadFloat4(&zeroPlane); }
	MirrorBall &GetRefletionBall(){ return reflectionBall; }

	void Init(ComPtr<ID3D11Device> device);
	void Render(RenderParams &params);
};

typedef Mirror<TextureVertexType, MirrorShader> SimpleMirror;

template<class vt, class sh>
Mirror<vt, sh>::Mirror(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader,
	int resWidth, int resHeight, float screenWidth, float screenHeight)
	:screen(screenPos, rot, screenModel, screenShader, nullptr, XMFLOAT3(screenWidth, screenHeight, 1.0f)),
	reflectionBall(resWidth, resHeight,
	([this](RenderParams &params) -> void
	{
		XMMATRIX reflectionMatrix = DirectX::XMMatrixReflect(GetMirrorPlane());
		XMMATRIX zeroReflect = DirectX::XMMatrixReflect(GetZeroPlane());
		params.view = params.camera->GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
		params.pass = PASS_TYPE_REFLECTION;
		XMStoreFloat4(&params.clipPlane, GetMirrorPlane());
	}))
{
	mirrorPlane = Utils::PlaneFromPointAndRot(screenPos, rot);
	zeroPlane = Utils::PlaneFromPointAndRot(ZeroVec3, rot);
	textures.push_back(nullptr);
}

template<class vt, class sh>
Mirror<vt, sh>::Mirror(Mirror &&other)
:screen(move(other.screen)), mirrorPlane(move(other.mirrorPlane)), zeroPlane(move(other.zeroPlane)), reflectionBall(move(other.reflectionBall)),
textures(move(other.textures))
{
}

template<class vt, class sh>
void Mirror<vt, sh>::Init(ComPtr<ID3D11Device> device)
{
	reflectionBall.Init(device);
	screen.Init(device);
}

template<class vt, class sh>
void Mirror<vt, sh>::Render(RenderParams &params)
{
	if (params.pass == PASS_TYPE_REFLECTION)
		return;
	textures[0] = reflectionBall.GetCurrentTexture();
	XMMATRIX reflectionMatrix = DirectX::XMMatrixReflect(GetMirrorPlane());
	XMMATRIX zeroReflect = DirectX::XMMatrixReflect(GetZeroPlane());
	params.reflecMatrix = params.camera->GetReflectedViewMatrix(reflectionMatrix, zeroReflect);
	screen.Render(params, textures);
}