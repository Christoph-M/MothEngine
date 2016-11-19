#pragma once

#include "..\Moth.Core.Datatypes.h"


namespace Moth {
	namespace Core {
		struct IObserverBase {
			virtual ~IObserverBase() { }
			virtual void OnNotify() = 0;
		};

		struct IObserverInput {
			virtual ~IObserverInput() { }
			virtual void OnInput(Moth_Int32) = 0;
			virtual void OnInputDown(Moth_Int32) = 0;
			virtual void OnInputUp(Moth_Int32) = 0;
			virtual void OnInputToggle(Moth_Int32) = 0;
		};
	}
}