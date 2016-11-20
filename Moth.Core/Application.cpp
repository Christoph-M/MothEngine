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
			assert(CHECK_TYPE(Moth_Int8, 1));
			assert(CHECK_TYPE(Moth_Int16, 2));
			assert(CHECK_TYPE(Moth_Int32, 4));
			assert(CHECK_TYPE(Moth_Int64, 8));
			assert(CHECK_TYPE(Moth_UInt8, 1));
			assert(CHECK_TYPE(Moth_UInt16, 2));
			assert(CHECK_TYPE(Moth_UInt32, 4));
			assert(CHECK_TYPE(Moth_UInt64, 8));
			assert(CHECK_TYPE(Moth_Char8, 1));
			assert(CHECK_TYPE(Moth_WChar16, 2));
			assert(CHECK_TYPE(Moth_Float32, 4));
			assert(CHECK_TYPE(Moth_Float64, 8));

			if (!Window::Instance()->MakeWindow()) {
				Window::LastErrorToConsole();
				Window::LastErrorToMessageBox();
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

		void Application::FacePlant() { DestroyWindow(Window::Instance()->GetWindow()); }


		Application::~Application() { }
	}
}