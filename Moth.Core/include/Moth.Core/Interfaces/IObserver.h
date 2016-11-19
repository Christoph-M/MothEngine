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
			virtual void OnInput(Moth_Int32, enum EKeyState) = 0;
		};
	}
}