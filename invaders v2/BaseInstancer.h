#pragma once
#include "DrawableEntity.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "includes.h"
#include "ArrayBuffer.h"
#include "Direct3D.h"

template<class vt, class sh, class it>
class BaseInstancer : public IDrawable
{
public:
	BaseInstancer(ID3D11Device *device, Model<vt> &model, sh &shader, uint capacity);
	BaseInstancer(BaseInstancer&&);
	virtual ~BaseInstancer(void){}

protected:
	uint capacity;
	uint instanceCount;

	e::vector<it> instanceData;

	ArrayBuffer<it> instanceBuffer;

	Model<vt> &model;
	sh &shader;
public:
	void Render(const RenderParams& params);

protected:
	virtual bool Update(ID3D11DeviceContext *context);
	void SetCapacity(int capacity);
};

typedef BaseInstancer<VertexType, ColorInstancedShader, InstanceType> SimpleBaseInstancer;

template<class vt, class sh, class it>
BaseInstancer<vt, sh, it>::BaseInstancer(ID3D11Device *device, Model<vt> &model, sh &shader, uint capacity)
:model(model), shader(shader), capacity(capacity), instanceBuffer(device, nullptr, false, capacity)
{
}

template<class vt, class sh, class it>
BaseInstancer<vt, sh, it>::BaseInstancer(BaseInstancer &&other)
: capacity(other.capacity), instanceCount(other.instanceCount),
model(other.model), shader(other.shader)
{
	e::swap(instanceData, other.instanceData);
	e::swap(instanceBuffer, other.instanceBuffer);
}

template<class vt, class sh, class it>
void BaseInstancer<vt, sh, it>::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	model.Set(params.context);
	params.context->IASetVertexBuffers(1, 1, instanceBuffer.GetAddressOf(), instanceBuffer.GetStride(), instanceBuffer.GetOffset());
	shader.SetShaderParametersInstanced(params);
	shader.RenderShaderInstanced(params.context, model.GetIndexCount(), instanceCount);
}

template<class vt, class sh, class it>
bool BaseInstancer<vt, sh, it>::Update(ID3D11DeviceContext *context)
{
	if(instanceCount == 0)
		return false;
	
	instanceBuffer.SetData(context, instanceData, instanceCount);

	return true;
}

template<class vt, class sh, class it>
void BaseInstancer<vt, sh, it>::SetCapacity(int capacity)
{
	this->capacity = capacity;
	this->instanceCount = 0;
	instanceBuffer = ArrayBuffer<it>(Direct3D::GetDevice(), nullptr, false, capacity);
}