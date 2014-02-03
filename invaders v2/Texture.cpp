#include "includes.h"
#include "Texture.h"
#include "Utils.h"
using namespace std;
Texture::Texture(ID3D11Device *device, uint width, uint height, uint view)
:view(view), width(width), height(height)
{
	D3D11_TEXTURE2D_DESC texDesc;
	uint bind = 0;

	if (view & TEXTURE_VIEW_SHADER_RESOURCE)
		bind |= D3D11_BIND_SHADER_RESOURCE;
	if (view & TEXTURE_VIEW_UNORDERED_ACCESS)
		bind |= D3D11_BIND_UNORDERED_ACCESS;
	if (view & TEXTURE_VIEW_RENDER_TARGET)
		bind |= D3D11_BIND_RENDER_TARGET;

	texDesc.ArraySize = 1;
	texDesc.BindFlags = bind;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.Height = height;
	texDesc.Width = width;
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	Assert(device->CreateTexture2D(&texDesc, NULL, &texture));

	if (view & TEXTURE_VIEW_SHADER_RESOURCE)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvdesc;
		srvdesc.Format = texDesc.Format;
		srvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvdesc.Texture2D.MipLevels = 1;
		srvdesc.Texture2D.MostDetailedMip = 0;

		Assert(device->CreateShaderResourceView(texture.Get(), &srvdesc, &shaderResourceView));
	}

	if (view & TEXTURE_VIEW_UNORDERED_ACCESS)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
		uavDesc.Format = texDesc.Format;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
		uavDesc.Texture2D.MipSlice = 0;

		Assert(device->CreateUnorderedAccessView(texture.Get(), &uavDesc, &unorderedAccessView));
	}

	if (view & TEXTURE_VIEW_RENDER_TARGET)
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = texDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;

		Assert(device->CreateRenderTargetView(texture.Get(), &rtvDesc, &renderTargetView));
	}
}

Texture::Texture(Texture &&other)
:texture(move(other.texture)), shaderResourceView(move(other.shaderResourceView)),
renderTargetView(move(other.renderTargetView)), unorderedAccessView(move(other.unorderedAccessView)),
view(other.view), width(other.width), height(other.height)
{
}