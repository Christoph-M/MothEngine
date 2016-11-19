#include "include\Moth.Core\Application.h"

#include "include\Moth.Core\Window.h"
#include "include\Moth.Core\Input.h"
#include "include\Moth.Core\Interfaces\IScene.h"


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
		{
			if (!Window::Instance()->MakeWindow()) {
				Window::LastErrorToConsole();
			}
			Input::Instance();
		}


		void Application::Run(IScene* scene) {
			scene->Begin();

			while (running_) {
				if (PeekMessage(&messages_, NULL, 0, 0, PM_REMOVE)) {
					TranslateMessage(&messages_);
					DispatchMessage(&messages_);

					running_ = messages_.message != WM_QUIT;
				}

				Input::Instance()->CheckInput();
				scene->Update();

				scene->Draw3D();
				scene->Draw2D();

				Sleep(1);
			}

			scene->End();
		}

		void Application::FacePlant() { DestroyWindow(Moth::Core::Window::Instance()->GetWindow()); }


		Application::~Application() { }
	}
}