#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Interfaces\IGraphics3D.h"


namespace Moth {
	namespace Core {
		class Application {
		public:
			Application();


			void Run(struct IScene*);
			LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
			static void FacePlant();


			~Application();


			Application(const Application&) = delete;

		private:
			bool running_;
			MSG messages_;
		};

		typedef Moth::Core::IGraphics3D* (*ALLOCATE_GRAPHICS3D)();
		typedef void (*RELEASE_GRAPHICS3D)(Moth::Core::IGraphics3D*);
	}
}