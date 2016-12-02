#pragma once

#include <Moth.Core\Interfaces\IGraphics3D.h>


namespace Moth {
	namespace Graphics3D {
		namespace DX {
			class DirectX : public Moth::Core::IGraphics3D {
			public:
				DirectX();


				bool Initialize();
				bool Shutdown();
				bool RenderFrame();


				~DirectX();
				

				DirectX(const DirectX&) = delete;

			private:
				class D3D* direct3D_;
			};

			inline Moth::Core::IGraphics3D* CreateGraphics3D() {
				return new DirectX();
			}

			inline void ReleaseGraphics3D(Moth::Core::IGraphics3D* graphics3D) {
				delete(graphics3D);
			}
		}
	}
}