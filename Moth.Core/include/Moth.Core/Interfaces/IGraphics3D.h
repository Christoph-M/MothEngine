#pragma once


namespace Moth {
	namespace Core {
		struct IGraphics3D {
			virtual bool Initialize() = 0;
			virtual bool Shutdown() = 0;
			virtual bool RenderFrame() = 0;
		};
	}
}