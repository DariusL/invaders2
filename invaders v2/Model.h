#pragma once

#include "Globals.h"
#include "Utils.h"

using namespace std;
using namespace Microsoft::WRL;
class ResourceManager;

template<class T>
class Model
{
public:
	Model(ComPtr<ID3D11Device> device, const vector<T> &vertices, const vector<int> &indices);
	Model(Model &&other);
	Model &operator=(Model &&other);

	Model(Model&) = delete;
	Model &operator=(Model&) = delete;

	void Set(ComPtr<ID3D11DeviceContext> context);

	int GetIndexCount(){ return indexCount; }
private:
	uint indexCount;

	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;
	BufferInfo vertexInfo;
};

typedef Model<VertexType> ColorModel;
typedef Model<NormalMappedVertexType> NormalMappedModel;
typedef Model<NormalVertexType> NormalModel;
typedef Model<TextureVertexType> TexturedModel;
typedef Model<NormalTextureVertexType> NormalTexturedModel;

template<class T>
Model<T>::Model(Model &&other)
:vertexBuffer(move(other.vertexBuffer)), indexBuffer(move(other.indexBuffer)),
vertexInfo(other.vertexInfo), indexCount(other.indexCount)
{
}

template<class T>
Model<T> &Model<T>::operator=(Model &&other)
{
	if (this != &other)
	{
		indexCount = other.indexCount;
		vertexInfo = other.vertexInfo;
		vertexBuffer = move(other.vertexBuffer);
		indexBuffer = move(other.indexBuffer);
	}
	return *this;
}

template<class T>
Model<T>::Model(ComPtr<ID3D11Device> device, const vector<T> &vertices, const vector<int> &indices)
:indexCount(indices.size())
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(T);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(T)* vertices.size();
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	vertexData.pSysMem = vertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer));

	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(int)* indices.size();
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	indexData.pSysMem = indices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer));
}

template<class T>
void Model<T>::Set(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
}