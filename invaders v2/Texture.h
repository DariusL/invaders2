#pragma once
#include "includes.h"
#include "Globals.h"
using namespace Microsoft::WRL;

enum TEXTURE_VIEW
{
	TEXTURE_VIEW_RENDER_TARGET = 1 << 0,
	TEXTURE_VIEW_SHADER_RESOURCE = 1 << 1,
	TEXTURE_VIEW_UNORDERED_ACCESS = 1 << 2
};

class Texture
{
	ComPtr<ID3D11Texture2D> texture;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	ComPtr<ID3D11UnorderedAccessView> unorderedAccessView;
	ComPtr<ID3D11RenderTargetView> renderTargetView;

	uint view;
	uint width, height;
public:
	Texture(ComPtr<ID3D11Device> device, uint width, uint height, uint view);
	Texture(Texture&) = delete;
	Texture(Texture&&);
	~Texture(){}

	ComPtr<ID3D11ShaderResourceView> GetSRV(){ return shaderResourceView; }
	ComPtr<ID3D11UnorderedAccessView> GetUAV(){ return unorderedAccessView; }
	ComPtr<ID3D11RenderTargetView> GetRTV(){ return renderTargetView; }

	uint GetWidth(){ return width; }
	uint Getheight(){ return height; }
};