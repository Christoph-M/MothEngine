#include "include\Moth.Graphics.DX\D3D.h"
#include "..\Moth.Core\include\Moth.Core\GraphicsSettings.h"

#include <Moth.Core\Moth.Core.h>

#include <DirectXMath.h>


namespace Moth {
	namespace Graphics3D {
		namespace DX {
			D3D::D3D() :
				adapterDescription_{ false, 0, { '\0' } },
				swapChain_(nullptr),
				device_(nullptr),
				deviceContext_(nullptr),
				renderTargetView_(nullptr),
				depthStencil_(nullptr),
				depthStencilState_(nullptr),
				depthStencilView_(nullptr),
				rasterizerState_(nullptr),
				modelMatrix_(Moth::Math::FMatrix::Identity()),
				orthoMatrix_(Moth::Math::FMatrix::Identity()),
				projectionMatrix_(Moth::Math::FMatrix::Identity())
			{ }


			bool D3D::Initialize() {
				if (!this->RetrieveAdapterDescription()) {
					Moth::Core::Window::LogToMessageBox(L"D3D::Initialize: Failed to retrieve adapter description", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
					return false;
				}
				if (!this->InitializeDeviceAndSwapChain()) {
					Moth::Core::Window::LogToMessageBox(L"D3D::Initialize: Failed to initialize device and swapchain", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
					return false;
				}
				if (!this->InitializeRenderTargets()) {
					Moth::Core::Window::LogToMessageBox(L"D3D::Initialize: Failed to initialize depth stencil", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
					return false;
				}
				if (!this->InitializeRasterizer()) {
					Moth::Core::Window::LogToMessageBox(L"D3D::Initialize: Failed to initialize rasterizer", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
					return false;
				}
				this->CreateMVPMatricies();

				return true;
			}

			bool D3D::StartDraw(const Moth::Math::FVector4& clearColor) const {
				deviceContext_->ClearRenderTargetView(renderTargetView_, clearColor.a);
				deviceContext_->ClearDepthStencilView(depthStencilView_, D3D11_CLEAR_DEPTH, 1.0f, 0);

				return true;
			}

			bool D3D::EndDraw() const {
				if (adapterDescription_.vSyncEnabled) swapChain_->Present(1, 0);
				else								  swapChain_->Present(0, 0);

				return true;
			}

			bool D3D::ShutDown() {
				if (swapChain_) swapChain_->SetFullscreenState(false, NULL);

				if (rasterizerState_) {
					rasterizerState_->Release();
					rasterizerState_ = nullptr;
				}
				if (depthStencilView_) {
					depthStencilView_->Release();
					depthStencilView_ = nullptr;
				}
				if (depthStencilState_) {
					depthStencilState_->Release();
					depthStencilState_ = nullptr;
				}
				if (depthStencil_) {
					depthStencil_->Release();
					depthStencil_ = nullptr;
				}
				if (renderTargetView_) {
					renderTargetView_->Release();
					renderTargetView_ = nullptr;
				}
				if (deviceContext_) {
					deviceContext_->Release();
					deviceContext_ = nullptr;
				}
				if (device_) {
					device_->Release();
					device_ = nullptr;
				}
				if (swapChain_) {
					swapChain_->Release();
					swapChain_ = nullptr;
				}

				return true;
			}

			bool D3D::RetrieveAdapterDescription() {
				IDXGIFactory* factory = nullptr;
				IDXGIAdapter* adapter = nullptr;
				IDXGIOutput* adapterOutput = nullptr;
				Moth_UInt32 numModes = 0;
				Moth_UInt64 stringLength = 0;
				DXGI_MODE_DESC* displayModeList = nullptr;
				DXGI_ADAPTER_DESC adapterDescription = { 0 };

				Moth::Core::Window::Description windowDescription = Moth::Core::Window::Instance()->GetDescription();

				adapterDescription_.vSyncEnabled = VSYNC_ENABLED;

				if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory)))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				if (FAILED(factory->EnumAdapters(0, &adapter))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				factory->Release();
				factory = nullptr;

				if (FAILED(adapter->EnumOutputs(0, &adapterOutput))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				displayModeList = new DXGI_MODE_DESC[numModes];
				if (!displayModeList) {
					Moth::Core::Window::LogToMessageBox(L"Failed to create D3D::RetrieveAdapterDescription::displayModeList", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
					return false;
				}

				if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				adapterOutput->Release();
				adapterOutput = nullptr;

				for (Moth_Int32 i = 0; i < numModes; ++i) {
					if (displayModeList[i].Width == static_cast<Moth_UInt32>(windowDescription.width)) {
						if (displayModeList[i].Height == static_cast<Moth_UInt32>(windowDescription.height)) {
							adapterDescription_.numerator = displayModeList[i].RefreshRate.Numerator;
							adapterDescription_.denominator = displayModeList[i].RefreshRate.Denominator;
						}
					}
				}

				delete[](displayModeList);
				displayModeList = nullptr;

				if (FAILED(adapter->GetDesc(&adapterDescription))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				adapter->Release();
				adapter = nullptr;

				adapterDescription_.videoMemory = static_cast<Moth_Int32>(adapterDescription.DedicatedVideoMemory / 1024 / 1024);

				if (wcstombs_s(&stringLength, reinterpret_cast<Moth_CString>(adapterDescription_.graphicsCardDescription), 128, adapterDescription.Description, 128) != 0) {
					Moth::Core::Window::LogToMessageBox(L"D3D::RetrieveAdapterDescription: Failed to get D3D::graphicsCardDescription_", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
					return false;
				}

				return true;
			}

			bool D3D::InitializeDeviceAndSwapChain() {
				DXGI_SWAP_CHAIN_DESC swapChainDescription = { 0 };
				D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
				ID3D11Texture2D* backBuffer = nullptr;

				Moth::Core::Window::Description windowDescription = Moth::Core::Window::Instance()->GetDescription();

				swapChainDescription.BufferCount = 1;
				swapChainDescription.BufferDesc.Width = windowDescription.width;
				swapChainDescription.BufferDesc.Height = windowDescription.height;
				swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				swapChainDescription.BufferDesc.RefreshRate.Numerator = (adapterDescription_.vSyncEnabled) ? adapterDescription_.numerator : 1;
				swapChainDescription.BufferDesc.RefreshRate.Denominator = (adapterDescription_.vSyncEnabled) ? adapterDescription_.denominator : 0;
				swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
				swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDescription.OutputWindow = Moth::Core::Window::Instance()->GetWindow();
				swapChainDescription.SampleDesc.Count = 1;
				swapChainDescription.SampleDesc.Quality = 0;
				swapChainDescription.Windowed = !FULL_SCREEN;
				swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				swapChainDescription.Flags = 0;

				if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevel, 2,
														 D3D11_SDK_VERSION, &swapChainDescription, &swapChain_, &device_, NULL, &deviceContext_))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				if (FAILED(swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				if (FAILED(device_->CreateRenderTargetView(backBuffer, NULL, &renderTargetView_))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				backBuffer->Release();
				backBuffer = nullptr;

				return true;
			}

			bool D3D::InitializeRenderTargets() {
				D3D11_TEXTURE2D_DESC depthBufferDescription = { 0 };
				D3D11_DEPTH_STENCIL_DESC depthStencilDescription = { 0 };
				D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription = { };

				Moth::Core::Window::Description windowDescription = Moth::Core::Window::Instance()->GetDescription();

				depthBufferDescription.Width = windowDescription.width;
				depthBufferDescription.Height = windowDescription.height;
				depthBufferDescription.MipLevels = 1;
				depthBufferDescription.ArraySize = 1;
				depthBufferDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				depthBufferDescription.SampleDesc.Count = 1;
				depthBufferDescription.SampleDesc.Quality = 0;
				depthBufferDescription.Usage = D3D11_USAGE_DEFAULT;
				depthBufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				depthBufferDescription.CPUAccessFlags = 0;
				depthBufferDescription.MiscFlags = 0;

				if (FAILED(device_->CreateTexture2D(&depthBufferDescription, NULL, &depthStencil_))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				depthStencilDescription.DepthEnable = true;
				depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;
				depthStencilDescription.StencilEnable = true;
				depthStencilDescription.StencilReadMask = 0xFF;
				depthStencilDescription.StencilWriteMask = 0xFF;
				depthStencilDescription.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDescription.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				depthStencilDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				depthStencilDescription.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				depthStencilDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				if (FAILED(device_->CreateDepthStencilState(&depthStencilDescription, &depthStencilState_))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				deviceContext_->OMSetDepthStencilState(depthStencilState_, 1);

				depthStencilViewDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				depthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilViewDescription.Texture2D.MipSlice = 0;

				if (FAILED(device_->CreateDepthStencilView(depthStencil_, &depthStencilViewDescription, &depthStencilView_))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				deviceContext_->OMSetRenderTargets(1, &renderTargetView_, depthStencilView_);

				return true;
			}

			bool D3D::InitializeRasterizer() {
				D3D11_RASTERIZER_DESC rasterizerDescription = { };

				rasterizerDescription.AntialiasedLineEnable = false;
				rasterizerDescription.CullMode = D3D11_CULL_BACK;
				rasterizerDescription.DepthBias = 0;
				rasterizerDescription.DepthBiasClamp = 0.0f;
				rasterizerDescription.DepthClipEnable = true;
				rasterizerDescription.FillMode = D3D11_FILL_SOLID;
				rasterizerDescription.FrontCounterClockwise = false;
				rasterizerDescription.MultisampleEnable = false;
				rasterizerDescription.ScissorEnable = false;
				rasterizerDescription.SlopeScaledDepthBias = 0.0f;

				if (FAILED(device_->CreateRasterizerState(&rasterizerDescription, &rasterizerState_))) {
					Moth::Core::Window::LastErrorToConsole();
					Moth::Core::Window::LastErrorToMessageBox();
					return false;
				}

				deviceContext_->RSSetState(rasterizerState_);

				return true;
			}

			void D3D::CreateMVPMatricies() {
				D3D11_VIEWPORT viewport;
				Moth_Float32 fieldOfView = 0.0f, aspectRatio = 0.0f;
				DirectX::XMFLOAT4X4 orthoMatrix, projectionMatrix;

				Moth::Core::Window::Description windowDescription = Moth::Core::Window::Instance()->GetDescription();

				viewport.Width = static_cast<float>(windowDescription.width);
				viewport.Height = static_cast<float>(windowDescription.height);
				viewport.MinDepth = 0.0f;
				viewport.MaxDepth = 1.0f;
				viewport.TopLeftX = 0.0f;
				viewport.TopLeftY = 0.0f;

				deviceContext_->RSSetViewports(1, &viewport);

				fieldOfView = PI / 4.0f;
				aspectRatio = viewport.Width / viewport.Height;

				DirectX::XMStoreFloat4x4(&orthoMatrix, DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicLH(viewport.Width, viewport.Height, SCREEN_NEAR, SCREEN_DEPTH)));
				DirectX::XMStoreFloat4x4(&projectionMatrix, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, SCREEN_NEAR, SCREEN_DEPTH)));

				orthoMatrix_ = Moth::Math::FMatrix(orthoMatrix.m[0][0], orthoMatrix.m[0][1], orthoMatrix.m[0][2], orthoMatrix.m[0][3],
												   orthoMatrix.m[1][0], orthoMatrix.m[1][1], orthoMatrix.m[1][2], orthoMatrix.m[1][3],
												   orthoMatrix.m[2][0], orthoMatrix.m[2][1], orthoMatrix.m[2][2], orthoMatrix.m[2][3],
												   orthoMatrix.m[3][0], orthoMatrix.m[3][1], orthoMatrix.m[3][2], orthoMatrix.m[3][3]);

				projectionMatrix_ = Moth::Math::FMatrix(projectionMatrix.m[0][0], projectionMatrix.m[0][1], projectionMatrix.m[0][2], projectionMatrix.m[0][3],
														projectionMatrix.m[1][0], projectionMatrix.m[1][1], projectionMatrix.m[1][2], projectionMatrix.m[1][3],
														projectionMatrix.m[2][0], projectionMatrix.m[2][1], projectionMatrix.m[2][2], projectionMatrix.m[2][3],
														projectionMatrix.m[3][0], projectionMatrix.m[3][1], projectionMatrix.m[3][2], projectionMatrix.m[3][3]);
			}


			D3D::~D3D() {
				
			}
		}
	}
}
