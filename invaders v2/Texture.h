#pragma once
#include "includes.h"
#include "Globals.h"

enum TEXTURE_VIEW
{
	TEXTURE_VIEW_RENDER_TARGET = 1 << 0,
	TEXTURE_VIEW_SHADER_RESOURCE = 1 << 1,
	TEXTURE_VIEW_UNORDERED_ACCESS = 1 << 2
};

class Texture
{
	e::ComPtr<ID3D11Texture2D> texture;
	e::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	e::ComPtr<ID3D11UnorderedAccessView> unorderedAccessView;
	e::ComPtr<ID3D11RenderTargetView> renderTargetView;

	uint view;
	uint width, height;
public:
	Texture(ID3D11Device *device, uint width, uint height, uint view);
	Texture(Texture&) = delete;
	Texture(Texture&&);
	~Texture(){}

	ID3D11ShaderResourceView *GetSRV(){ return shaderResourceView.Get(); }
	ID3D11UnorderedAccessView *GetUAV(){ return unorderedAccessView.Get(); }
	ID3D11RenderTargetView *GetRTV(){ return renderTargetView.Get(); }

	uint GetWidth(){ return width; }
	uint Getheight(){ return height; }
};