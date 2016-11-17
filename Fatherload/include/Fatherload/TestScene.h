#pragma once


#include "Moth.Core\Interfaces\IScene.h"


namespace Fatherload {
	class TestScene : public Moth::Core::IScene {
	public:
		void Begin();
		void Update();
		void Draw2D();
		void Draw3D();
		void End();
	};
}