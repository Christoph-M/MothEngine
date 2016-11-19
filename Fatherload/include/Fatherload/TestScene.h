#pragma once


#include "Moth.Core\Interfaces\IScene.h"
#include "Moth.Core\Interfaces\IObserver.h"


namespace Fatherload {
	class TestScene : public Moth::Core::IScene, public Moth::Core::IObserverInput {
	public:
		void Begin();
		void Update();
		void Draw2D();
		void Draw3D();
		void End();
		void OnInput(Moth_Int32);
		void OnInputDown(Moth_Int32);
		void OnInputUp(Moth_Int32);
		void OnInputToggle(Moth_Int32);
	};
}