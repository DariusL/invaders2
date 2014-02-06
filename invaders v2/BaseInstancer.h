#pragma once
#include "DrawableEntity.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "includes.h"

using namespace std;
using namespace Microsoft::WRL;

template<class vt, class sh, class it>
class BaseInstancer : public DrawableEntity<vt, sh>
{
public:
	BaseInstancer(ID3D11Device *device, Model<vt> &model, sh &shader, int maxObjectCount, XMFLOAT3 pos = XMFLOAT3());
	virtual ~BaseInstancer(void){}

protected:
	int maxInstanceCount;
	int instanceCount;

	vector<it> instanceData;

	ComPtr<ID3D11Buffer> instanceBuffer;
	BufferInfo instanceInfo;
public:
	void Render(const RenderParams& params);

protected:
	virtual bool Update(ID3D11DeviceContext *context);
};

typedef BaseInstancer<VertexType, ColorInstancedShader, InstanceType> SimpleBaseInstancer;

template<class vt, class sh, class it>
BaseInstancer<vt, sh, it>::BaseInstancer(ID3D11Device *device, Model<vt> &model, sh &shader, int maxObjectCount, XMFLOAT3 pos)
	:DrawableEntity(pos, model, shader)
{
	this->maxInstanceCount = maxObjectCount;

	D3D11_BUFFER_DESC instanceBufferDesc;

	ZeroMemory(&instanceBufferDesc, sizeof(instanceBufferDesc));
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(it)* maxInstanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	Assert(device->CreateBuffer(&instanceBufferDesc, NULL, &instanceBuffer));

	instanceInfo.offset = 0;
	instanceInfo.stride = sizeof(it);
}

template<class vt, class sh, class it>
void BaseInstancer<vt, sh, it>::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	model.Set(params.context);
	params.context->IASetVertexBuffers(1, 1, instanceBuffer.GetAddressOf(), &instanceInfo.stride, &instanceInfo.offset);
	shader.SetShaderParametersInstanced(params);
	shader.RenderShaderInstanced(params.context, model.GetIndexCount(), instanceCount);
}

template<class vt, class sh, class it>
bool BaseInstancer<vt, sh, it>::Update(ID3D11DeviceContext *context)
{
	if(instanceCount == 0)
		return false;
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, instanceData.data(), sizeof(it) * instanceCount);

	context->Unmap(instanceBuffer.Get(), 0);

	return true;
}