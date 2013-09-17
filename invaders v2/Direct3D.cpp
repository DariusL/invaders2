#include "includes.h"
#include "Direct3D.h"


Direct3D::Direct3D(void)
{
}

Direct3D::~Direct3D()
{
	if(swapChain)
	{
		swapChain->SetFullscreenState(false, NULL);
	}
}

bool Direct3D::Init(int width, int height, bool vsync, HWND whandle, bool fullscreen, float screendepth, float screennear)
{
	ComPtr<IDXGIFactory> factory;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<IDXGIOutput> adapterOutput;
	unsigned int numModes, numerator, denominator, stringLength;
	unique_ptr<DXGI_MODE_DESC[]> displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ComPtr<ID3D11Texture2D> backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;
	this->vsync = vsync;

	clearColor[0] = 0.0f;
	clearColor[1] = 0.0f;
	clearColor[2] = 0.0f;
	clearColor[3] = 1.0f;

	Assert(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));
	Assert(factory->EnumAdapters(0, &adapter));
	Assert(adapter->EnumOutputs(0, &adapterOutput));
	Assert(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));
	displayModeList = unique_ptr<DXGI_MODE_DESC[]>(new DXGI_MODE_DESC[numModes]);
	Assert(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList.get()));
	for(unsigned int i = 0; i < numModes; i++)
		if(displayModeList[i].Height == height && displayModeList[i].Width == width)
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
			break;
		}
	Assert(adapter->GetDesc(&adapterDesc));
	videoMem = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
	wcstombs_s(&stringLength, videoDesc, 128, adapterDesc.Description, 128);

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	if(vsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	} 
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	}
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = whandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullscreen;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
	featureLevel = D3D_FEATURE_LEVEL_10_0;

	Assert(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc,
		&swapChain, &device, NULL, &deviceContext));
	Assert(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferPtr));
	Assert(device->CreateRenderTargetView(backBufferPtr.Get(), NULL, &renderTargetView));

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	Assert(device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer));

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	Assert(device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState))
	deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 1);

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	Assert(device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, &depthStencilView));
	deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());

	ZeroMemory(&rasterDesc, sizeof(rasterDesc));
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	Assert(device->CreateRasterizerState(&rasterDesc, &rasterState))
	deviceContext->RSSetState(rasterState.Get());

	ZeroMemory(&viewport, sizeof(viewport));
	viewport.Width = (FLOAT) width;
	viewport.Height = (FLOAT) height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	deviceContext->RSSetViewports(1, &viewport);

	fieldOfView = (FLOAT) D3DX_PI / 4.0f;
	screenAspect = width / (float)height;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, fieldOfView, screenAspect, screennear, screendepth);
	D3DXMatrixOrthoLH(&orthoMatrix, (FLOAT) width, (FLOAT) height, screennear, screendepth);
	return true;
}

void Direct3D::BeginScene()
{
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);
	deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D::EndScene()
{
	if(vsync)
		swapChain->Present(1, 0);
	else
		swapChain->Present(0, 0);
}