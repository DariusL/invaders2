#pragma once
#include "includes.h"
#include "Utils.h"
template<class T>
class Buffer
{
	e::ComPtr<ID3D11Buffer> buffer;
	bool immutable;
public:
	Buffer(ID3D11Device *device = nullptr, const T *data = nullptr, bool immutable = false);
	Buffer(const Buffer&) = delete;
	Buffer &operator=(Buffer&&);
	ID3D11Buffer *Get(){ return buffer.Get(); }
	ID3D11Buffer **GetAddressOf(){ return buffer.GetAddressOf(); }
	void SetData(ID3D11DeviceContext *context, const T &data);
};

template<class T>
Buffer<T>::Buffer(ID3D11Device *device, const T *data, bool immutable)
:immutable(immutable)
{
	using namespace e;
	if (device == nullptr)
		return;
	AssertBool(!(data == nullptr && immutable), L"Tried to create an immutable buffer with no initial data");
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource, *rptr = nullptr;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(T);
	desc.CPUAccessFlags = immutable ? 0 : D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = immutable ? D3D11_USAGE_IMMUTABLE : D3D11_USAGE_DYNAMIC;

	if (data)
	{
		resource.pSysMem = data;
		resource.SysMemPitch = 0;
		resource.SysMemSlicePitch = 0;
		rptr = &resource;
	}

	Assert(device->CreateBuffer(&desc, rptr, &buffer));
}

template<class T>
Buffer<T> &Buffer<T>::operator=(Buffer<T> &&other)
{
	if (this != &other)
	{
		e::swap(immutable, other.immutable);
		e::swap(buffer, other.buffer);
	}
	return *this;
}

template<class T>
void Buffer<T>::SetData(ID3D11DeviceContext *context, const T &data)
{
	Utils::CopyToBuffer(Get(), data, context);
}