#pragma once

#include "includes.h"
#include "DrawableTexturedEntity.h"

template<class vt, class sh>
class Billboard : public DrawableTexturedEntity<vt, sh>
{
public:
	Billboard(XMFLOAT3 pos, Model<vt> &model, sh &shader, ComPtr<ID3D11ShaderResourceView> texture = NULL, XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f));
	virtual void Render(RenderParams &renderParams);
};

template<class vt, class sh>
Billboard<vt, sh>::Billboard(XMFLOAT3 pos, Model<vt> &model, sh &shader, ComPtr<ID3D11ShaderResourceView> texture, XMFLOAT3 scale)
:DrawableTexturedEntity(pos, ZeroVec3, model, shader, texture, scale)
{
}

template<class vt, class sh>
void Billboard<vt, sh>::Render(RenderParams &renderParams)
{
	XMFLOAT3 camera = renderParams.camera->GetPosition();
	float angle = atan2(pos.x - camera.x, pos.z - camera.z);
	XMStoreFloat4x4(&this->rot, XMMatrixRotationY(angle));
	DrawableTexturedEntity::Render(renderParams);
}