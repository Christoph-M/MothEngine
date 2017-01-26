#pragma once


namespace Moth {
	namespace Core {
		class Window;

		struct IGraphics3D {
			virtual bool Initialize(Moth::Core::Window*) = 0;
			virtual bool Shutdown() = 0;
			virtual bool RenderFrame() = 0;
		};
	}
}