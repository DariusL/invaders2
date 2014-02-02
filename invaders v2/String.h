#pragma once
#include "includes.h"
#include "IDrawableObject.h"
#include "Model.h"
#include "ColorShader.h"
#include "ResourceManager.h"
#include "AppendableGeometry.h"

using namespace DirectX;

template<class sh>
class String : public IDrawableObject
{
protected:
	ColorModel model;
	XMFLOAT4X4 moveMatrix;
	sh &shader;
	XMFLOAT3 pos;
public:
	String(XMFLOAT3 pos, string text, ComPtr<ID3D11Device> device, sh &shader);
	String(String &&other);
	virtual ~String(){}
	virtual void Render(RenderParams &params);
protected:
	virtual bool Update(ComPtr<ID3D11DeviceContext> context);
};

template<class sh>
String<sh>::String(XMFLOAT3 pos, string text, ComPtr<ID3D11Device> device, sh &shader)
:pos(pos), shader(shader), IDrawableObject()
{
	ResourceManager &rm = RM::Get();
	AppendableGeometry<VertexType> geometry(0.0f);
	for (auto &c : text)
	{
		geometry += rm.GetLetter(c);
	}
	model = ColorModel(device, geometry);
}

template<class sh>
String<sh>::String(String &&other)
:IDrawableObject(move(other)), pos(move(other.pos))
model(move(other.model)), shader(move(other.shader)),
moveMatrix(move(other.moveMatrix))
{
}

template<class sh>
void String<sh>::Render(RenderParams &params)
{
	if (!Update(params.context))
		return;
	model.Set(params.context);
	XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, world);
	shader.RenderShader(params.context, model.GetIndexCount());
}

template<class sh>
bool String<sh>::Update(ComPtr<ID3D11DeviceContext> context)
{
	XMStoreFloat4x4(&moveMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	return true;
}