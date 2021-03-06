#include "includes.h"
#include "Direct3D.h"
#include "Settings.h"

ID3D11Device *Direct3D::staticDevice = nullptr;
ID3D11DeviceContext *Direct3D::staticContext = nullptr;
bool Direct3D::compute;

Direct3D::Direct3D(int width, int height, bool vsync, HWND whandle, bool fullscreen, float screendepth, float screennear)
{
	e::ComPtr<IDXGIFactory> factory;
	e::ComPtr<IDXGIAdapter> adapter;
	e::ComPtr<IDXGIOutput> adapterOutput;
	unsigned int numModes, numerator, denominator, stringLength;
	e::unique_ptr<DXGI_MODE_DESC[]> displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	e::ComPtr<ID3D11Texture2D> backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
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
	displayModeList = e::unique_ptr<DXGI_MODE_DESC[]>(new DXGI_MODE_DESC[numModes]);
	Assert(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList.get()));
	for (unsigned int i = 0; i < numModes; i++)
		if (displayModeList[i].Height == height && displayModeList[i].Width == width)
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
	if (vsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	}
	swapChainDesc.OutputWindow = whandle;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullscreen;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL *featureLevel = new D3D_FEATURE_LEVEL[6]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	int debug = D3D11_CREATE_DEVICE_SINGLETHREADED;

#ifdef _DEBUG
	debug = D3D11_CREATE_DEVICE_DEBUG;
#endif
	Assert(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, debug, featureLevel, 6, D3D11_SDK_VERSION, &device, nullptr, &deviceContext));

	compute = device->GetFeatureLevel() == D3D_FEATURE_LEVEL_11_0;

	if (compute)
		swapChainDesc.BufferUsage |= DXGI_USAGE_UNORDERED_ACCESS;

	if (!compute)
		Settings::Get().SetValue(Settings::KEY_POST, 0);

	Assert(factory->CreateSwapChain(device.Get(), &swapChainDesc, &swapChain));

	delete[] featureLevel;

	Assert(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferPtr));
	Assert(device->CreateRenderTargetView(backBufferPtr.Get(), NULL, &renderTargetView));
	if (compute)
		Assert(device->CreateUnorderedAccessView(backBufferPtr.Get(), nullptr, &backBufferAccess));

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

	Assert(device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState));
	depthStencilDesc.DepthEnable = false;
	Assert(device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState2d));

	DoingDepthCheck(true);

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	Assert(device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, &depthStencilView));
	ResetRenderTarget();

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

	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	fieldOfView = e::XM_PI / 4.0f;
	screenAspect = width / (float)height;
	XMStoreFloat4x4(&projectionMatrix, e::XMMatrixPerspectiveFovRH(fieldOfView, screenAspect, screennear, screendepth));
	XMStoreFloat4x4(&orthoMatrix, e::XMMatrixOrthographicRH(static_cast<float>(width), static_cast<float>(height), screennear, screendepth));

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Assert(device->CreateBlendState(&blendDesc, &blendState));
	e::XMFLOAT4 blendFactor(0.0f, 0.0f, 0.0f, 0.0f);
	deviceContext->OMSetBlendState(blendState.Get(), reinterpret_cast<float*>(&blendFactor), static_cast<UINT>(-1));

	staticContext = deviceContext.Get();
	staticDevice = device.Get();
}

Direct3D::~Direct3D()
{
	if(swapChain)
		swapChain->SetFullscreenState(false, NULL);
}

void Direct3D::ClearRenderTarget()
{
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);
	deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D::Present()
{
	if(vsync)
		swapChain->Present(1, 0);
	else
		swapChain->Present(0, 0);
}

void Direct3D::ResetRenderTarget()
{
	deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
	deviceContext->RSSetViewports(1, &viewport);
}

void Direct3D::UnsetRenderTarget()
{
	deviceContext->OMSetRenderTargets(0, nullptr, nullptr);
}

void Direct3D::DoingDepthCheck(bool check)
{
	if(check)
		deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 1);
	else
		deviceContext->OMSetDepthStencilState(depthStencilState2d.Get(), 1);
}