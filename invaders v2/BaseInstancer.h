#pragma once
#include "DrawableEntity.h"
#include "Model.h"
#include "ColorInstancedShader.h"
#include "includes.h"
#include "ArrayBuffer.h"

using namespace std;
using namespace Microsoft::WRL;

template<class vt, class sh, class it>
class BaseInstancer : public IDrawable
{
public:
	BaseInstancer(ID3D11Device *device, Model<vt> &model, sh &shader, int maxObjectCount);
	BaseInstancer(BaseInstancer&&);
	virtual ~BaseInstancer(void){}

protected:
	int maxInstanceCount;
	int instanceCount;

	vector<it> instanceData;

	ArrayBuffer<it> instanceBuffer;

	Model<vt> &model;
	sh &shader;
public:
	void Render(const RenderParams& params);

protected:
	virtual bool Update(ID3D11DeviceContext *context);
};

typedef BaseInstancer<VertexType, ColorInstancedShader, InstanceType> SimpleBaseInstancer;

template<class vt, class sh, class it>
BaseInstancer<vt, sh, it>::BaseInstancer(ID3D11Device *device, Model<vt> &model, sh &shader, int maxObjectCount)
:model(model), shader(shader), maxInstanceCount(maxObjectCount), instanceBuffer(device, nullptr, false, maxObjectCount)
{
}

template<class vt, class sh, class it>
BaseInstancer<vt, sh, it>::BaseInstancer(BaseInstancer &&other)
: maxInstanceCount(other.maxInstanceCount), instanceCount(other.instanceCount),
model(other.model), shader(other.shader)
{
	swap(instanceData, other.instanceData);
	swap(instanceBuffer, other.instanceBuffer);
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