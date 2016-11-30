#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "..\Moth.Core.Datatypes.h"


namespace Moth {
	namespace Core {
		struct IGraphics3D {
			virtual bool Initialize(Moth_Int32, Moth_Int32, HWND) = 0;
		};
	}
}