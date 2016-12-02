#include "include\Moth.Graphics.DX\DirectX.h"

#include <Moth.Core\Moth.Core.h>

#include "include\Moth.Graphics.DX\D3D.h"


namespace Moth {
	namespace Graphics3D {
		namespace DX {
			DirectX::DirectX() :
				direct3D_(nullptr)
			{ }


			bool DirectX::Initialize() {
				direct3D_ = new D3D();
				if (!direct3D_) return false;

				if (direct3D_->Initialize()) {
					Moth::Core::Window::LogToMessageBox(L"DirectX: Failed to initialize Direct3D", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
					return false;
				}

				return true;
			}

			bool DirectX::Shutdown() {
				if (direct3D_) {
					if (!direct3D_->ShutDown()) {
						Moth::Core::Window::LogToMessageBox(L"DirectX: Failed to shutdown Direct3D", L"Error", MB_DEFBUTTON1 | MB_ICONERROR);
						return false;
					}

					delete(direct3D_);
					direct3D_ = nullptr;
				}

				return true;
			}

			bool DirectX::RenderFrame() {
				if (direct3D_->StartDraw(Moth::Math::FVector4 { 0.5f, 0.5f, 0.5f, 1.0f })) return false;
				if (direct3D_->EndDraw()) return false;

				return true;
			}


			DirectX::~DirectX() { }
		}
	}
}