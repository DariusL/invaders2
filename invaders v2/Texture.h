#pragma once
#include "includes.h"
#include "Globals.h"
using namespace Microsoft::WRL;
class Texture
{
	ComPtr<ID3D11Texture2D> texture;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	ComPtr<ID3D11UnorderedAccessView> unorderedAccessView;
	ComPtr<ID3D11RenderTargetView> renderTargetView;

	bool hasSRV, hasUAV, hasRTV;
	uint width, height;
public:
	Texture(uint width, uint height, bool createSRV = true, bool createRTV = true, bool createUAV = false) 
		:hasSRV(createSRV), hasUAV(createUAV), hasRTV(createRTV), width(width), height(height){}
	~Texture(){}

	void Init(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11ShaderResourceView> GetSRV(){ return shaderResourceView; }
	ComPtr<ID3D11UnorderedAccessView> GetUAV(){ return unorderedAccessView; }
	ComPtr<ID3D11RenderTargetView> GetRTV(){ return renderTargetView; }

	uint GetWidth(){ return width; }
	uint Getheight(){ return height; }
};