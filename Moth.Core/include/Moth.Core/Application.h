#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


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
	}
}