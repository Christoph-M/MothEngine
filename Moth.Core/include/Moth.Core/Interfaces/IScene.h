#pragma once


namespace Moth {
	namespace Core {
		class IGraphics3D;

		struct IScene {
			virtual void Begin() = 0;
			virtual void Update() = 0;
			virtual void Draw2D() = 0;
			virtual void Draw3D(IGraphics3D*) = 0;
			virtual void End() = 0;
		};
	}
}