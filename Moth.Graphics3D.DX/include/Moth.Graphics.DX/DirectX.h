#pragma once

#define MOTH_LIB_EXPORT

#include <Moth.Core\Interfaces\IGraphics3D.h>
#include <Moth.Core\Moth.Core.h>


namespace Moth {
	namespace Graphics3D {
		namespace DX {
			class DirectX : public Moth::Core::IGraphics3D {
			public:
				DirectX();


				bool Initialize(Moth::Core::Window*);
				bool Shutdown();
				bool RenderFrame();


				~DirectX();
				

				DirectX(const DirectX&) = delete;

			private:
				class D3D* direct3D_;
			};

			MOTHLIB Moth::Core::IGraphics3D* CreateGraphics3D() {
				return new DirectX();
			}

			MOTHLIB void ReleaseGraphics3D(Moth::Core::IGraphics3D* graphics3D) {
				delete(graphics3D);
				graphics3D = nullptr;
			}
		}
	}
}
