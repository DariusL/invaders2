#pragma once
#include "includes.h"
#include "Utils.h"

template<class T>
class ArrayBuffer
{
	e::ComPtr<ID3D11Buffer> buffer;
	bool immutable;
	uint offset, stride;
public:
	ArrayBuffer(ID3D11Device *device = nullptr, const e::vector<T> *data = nullptr, bool immutable = true, uint count = 0);
	ArrayBuffer(const ArrayBuffer&) = delete;
	ArrayBuffer &operator=(ArrayBuffer&&);
	ArrayBuffer(ArrayBuffer&&);
	ID3D11Buffer *Get(){ return buffer.Get(); }
	ID3D11Buffer **GetAddressOf(){ return buffer.GetAddressOf(); }
	uint *GetOffset(){ return &offset; }
	uint *GetStride(){ return &stride; }
	void SetData(ID3D11DeviceContext *context, const e::vector<T> &data, uint count = 0);
};

template<class T>
ArrayBuffer<T>::ArrayBuffer(ID3D11Device *device, const e::vector<T> *data, bool immutable, uint count)
:immutable(immutable)
{
	using namespace e;
	if (device == nullptr)
		return;
	offset = 0;
	stride = sizeof(T);
	AssertBool(!(data == nullptr && immutable), e::wstring(L"Tried to create an immutable buffer with no initial data"));
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource, *rptr = nullptr;

	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(T) * (count != 0 ? count : data->size());
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
		e::swap(immutable, other.immutable);
		e::swap(buffer, other.buffer);
		e::swap(stride, other.stride);
		e::swap(offset, other.offset);
	}
	return *this;
}

template<class T>
ArrayBuffer<T>::ArrayBuffer(ArrayBuffer &&other)
:buffer(e::move(other.buffer)),
immutable(e::move(other.immutable)),
offset(e::move(other.offset)),
stride(e::move(other.stride))
{
}

template<class T>
void ArrayBuffer<T>::SetData(ID3D11DeviceContext *context, const e::vector<T> &data, uint count)
{
	Utils::CopyToBuffer(Get(), context, data, count);
}