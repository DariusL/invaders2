#include "includes.h"
#include "Globals.h"
#include "App.h"

using namespace DirectX;

const XMFLOAT3 OneVec3 = XMFLOAT3(1.0f, 1.0f, 1.0f);
const XMFLOAT3 ZeroVec3 = XMFLOAT3(0.0f, 0.0f, 0.0f);
const XMFLOAT4 ZeroVec4 = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
const XMFLOAT2 ZeroVec2 = XMFLOAT2(0.0f, 0.0f);

const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> nullResourceView;
const Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> nullUnorderedView;
const Microsoft::WRL::ComPtr<ID3D11RenderTargetView> nullRenderTargetView;



LRESULT CALLBACK MsgRedirect(HWND h, UINT u, WPARAM w, LPARAM l)
{ 
	return AppHandle::Get().MessageHandler(h, u, w, l);
}