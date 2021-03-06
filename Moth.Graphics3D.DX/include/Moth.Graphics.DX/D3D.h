#pragma once

#include <d3d11.h>

#include <Moth.Core\Moth.Core.h>
#include <Moth.Math\Moth.Math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")


namespace Moth {
	namespace Graphics3D {
		namespace DX {
			class D3D {
			public:
				struct AdapterDescription {
					bool vSyncEnabled;
					Moth_Int32 videoMemory;
					Moth_UInt32 numerator;
					Moth_UInt32 denominator;
					Moth_Char graphicsCardDescription[128];
				};

			public:
				D3D();


				bool Initialize(Moth::Core::Window*);

				const ID3D11Device* Device() const { return device_; }
				const ID3D11DeviceContext* DeviceContext() const { return deviceContext_; }
				Moth::Math::FMatrix ModelMatrix() const { return modelMatrix_; }
				Moth::Math::FMatrix OrthoMatrix() const { return orthoMatrix_; }
				Moth::Math::FMatrix ProjectionMatrix() const { return projectionMatrix_; }
				const AdapterDescription& GetAdapterDescription() const { return adapterDescription_; }

				bool StartDraw(const Moth::Math::FVector4&) const;
				bool EndDraw() const;

				bool ShutDown();


				~D3D();

			private:
				bool RetrieveAdapterDescription();
				bool InitializeDeviceAndSwapChain();
				bool InitializeRenderTargets();
				bool InitializeRasterizer();
				void CreateMVPMatricies();

			private:
				Moth::Core::Window* window_;
				AdapterDescription adapterDescription_;
				IDXGISwapChain* swapChain_;
				ID3D11Device* device_;
				ID3D11DeviceContext* deviceContext_;
				ID3D11RenderTargetView* renderTargetView_;
				ID3D11Texture2D* depthStencil_;
				ID3D11DepthStencilState* depthStencilState_;
				ID3D11DepthStencilView* depthStencilView_;
				ID3D11RasterizerState* rasterizerState_;
				Moth::Math::FMatrix modelMatrix_;
				Moth::Math::FMatrix orthoMatrix_;
				Moth::Math::FMatrix projectionMatrix_;
			};
		}
	}
}