#pragma once
#include "includes.h"
#include "Utils.h"
using namespace Microsoft::WRL;
using namespace std;
template<class T>
class ArrayBuffer
{
	ComPtr<ID3D11Buffer> buffer;
	bool immutable;
	uint offset, stride;
public:
	ArrayBuffer(ID3D11Device *device = nullptr, const vector<T> *data = nullptr, bool immutable = true);
	ArrayBuffer(const ArrayBuffer&) = delete;
	ArrayBuffer &operator=(ArrayBuffer&&);
	ArrayBuffer(ArrayBuffer&&);
	ID3D11Buffer *Get(){ return buffer.Get(); }
	ID3D11Buffer **GetAddressOf(){ return buffer.GetAddressOf(); }
	uint *GetOffset(){ return &offset; }
	uint *GetStride(){ return &stride; }
	void SetData(ID3D11DeviceContext *context, const vector<T> &data);
};

template<class T>
ArrayBuffer<T>::ArrayBuffer(ID3D11Device *device, const vector<T> *data, bool immutable)
:immutable(immutable)
{
	if (device == nullptr)
		return;
	offset = 0;
	stride = sizeof(T);
	AssertBool(!(data == nullptr && immutable), L"Tried to create an immutable buffer with no initial data");
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource, *rptr = nullptr;

	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(T) * data->size();
	desc.CPUAccessFlags = immutable ? 0 : D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = immutable ? D3D11_USAGE_IMMUTABLE : D3D11_USAGE_DYNAMIC;

	if (data)
	{
		resource.pSysMem = data->data();
		resource.SysMemPitch = 0;
		resource.SysMemSlicePitch = 0;
		rptr = &resource;
	}

	Assert(device->CreateBuffer(&desc, rptr, &buffer));
}

template<class T>
ArrayBuffer<T> &ArrayBuffer<T>::operator=(ArrayBuffer<T> &&other)
{
	if (this != &other)
	{
		swap(immutable, other.immutable);
		swap(buffer, other.buffer);
		swap(stride, other.stride);
		swap(offset, other.offset);
	}
	return *this;
}

template<class T>
ArrayBuffer<T>::ArrayBuffer(ArrayBuffer &&other)
:buffer(move(other.buffer)),
immutable(move(other.immutable)),
offset(move(other.offset)),
stride(move(other.stride))
{
}

template<class T>
void ArrayBuffer<T>::SetData(ID3D11DeviceContext *context, const vector<T> &data)
{
	Utils::CopyToBuffer(Get(), data.data() * sizeof(T), context);
}