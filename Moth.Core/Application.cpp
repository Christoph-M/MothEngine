#include "Application.h"

#include "Window.h"


namespace Moth {
	namespace Core {
		LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch (message) {
				case WM_CLOSE:
					DestroyWindow(hwnd);
					return 0;
					break;
				case WM_DESTROY:
					PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
					break;
				default: break;
			}

			return DefWindowProc(hwnd, message, wParam, lParam);
		}


		Application::Application() :
			running_(true),
			messages_({ 0 })
		{ }


		void Application::Run() {
			while (running_) {
				if (PeekMessage(&messages_, NULL, 0, 0, PM_REMOVE)) {
					TranslateMessage(&messages_);
					DispatchMessage(&messages_);

					running_ = messages_.message != WM_QUIT;
				}
			}
		}


		Application::~Application() { }
	}
}