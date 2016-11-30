#include "include\Moth.Core\Application.h"

#include "include\Moth.Core\Window.h"
#include "include\Moth.Core\Input.h"
#include "include\Moth.Core\Interfaces\IScene.h"


namespace Moth {
	namespace Core {
		static Application* g_AppHandle = nullptr;

		LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch (message) {
				case WM_CLOSE:
					PostQuitMessage(0);
					return 0;
				case WM_DESTROY:
					PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
					return 0;
				default: break;
			}

			return g_AppHandle->MessageHandler(hwnd, message, wParam, lParam);
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
			assert(CHECK_TYPE(Moth_Char16, 2));
			assert(CHECK_TYPE(float, 4));
			assert(CHECK_TYPE(double, 8));

			if (!Window::Instance()) {
				Window::LogToConsole(L"Window instance = nullptr");
				Window::LogToMessageBox(L"Window instance = nullptr");
			}
			
			if (!Window::Instance()->MakeWindow()) {
				Window::LastErrorToConsole();
				Window::LastErrorToMessageBox();
			}
			Input::Instance();

			g_AppHandle = this;
		}


		LRESULT Application::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch (message) {
				default: break;
			}

			return DefWindowProc(hwnd, message, wParam, lParam);
		}

		void Application::Run(IScene* scene) {
			scene->Begin();

			while (running_) {
				if (PeekMessage(&messages_, NULL, 0, 0, PM_REMOVE)) {
					TranslateMessage(&messages_);
					DispatchMessage(&messages_);
				}

				if (messages_.message == WM_QUIT || Input::GetKey(VK_ESCAPE)) {
					running_ = false;
				} else {
					Input::Instance()->CheckInput();
					scene->Update();

					scene->Draw3D();
					scene->Draw2D();

					Sleep(1);
				}
			}

			scene->End();

			this->FacePlant();
		}

		void Application::FacePlant() {
			if (!Window::Instance()->EndWindow()) {
				Window::LastErrorToConsole();
				Window::LastErrorToMessageBox();
			}

			g_AppHandle = nullptr;
		}


		Application::~Application() { }
	}
}