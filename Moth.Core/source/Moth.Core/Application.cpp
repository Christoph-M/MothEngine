#include "..\..\include\Moth.Core\Application.h"

#include "..\..\include\Moth.Core\Window.h"
#include "..\..\include\Moth.Core\Input.h"
#include "..\..\include\Moth.Core\Interfaces\IScene.h"


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
			assert(CHECK_TYPE(Moth_WChar16, 2));
			assert(CHECK_TYPE(Moth_Float32, 4));
			assert(CHECK_TYPE(Moth_Float64, 8));

			if (!Window::InstancePtr()) {
				Window::LogToConsole(L"Window instance = nullptr");
				Window::LogToMessageBox(L"Window instance = nullptr");
			}
			
			if (!Window::Instance().MakeWindow()) {
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
			HMODULE graphics3DModule = LoadLibrary(L".\\data\\modules\\Moth.Graphics3D.DX.dll");
			ALLOCATE_GRAPHICS3D CreateGraphics3D = reinterpret_cast<ALLOCATE_GRAPHICS3D>(GetProcAddress(graphics3DModule, "CreateGraphics3D"));
			RELEASE_GRAPHICS3D ReleaseGraphics3D = reinterpret_cast<RELEASE_GRAPHICS3D>(GetProcAddress(graphics3DModule, "ReleaseGraphics3D"));
			Moth::Core::IGraphics3D* graphics3D = CreateGraphics3D();

			graphics3D->Initialize(Window::InstancePtr());

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

					scene->Draw3D(graphics3D);
					scene->Draw2D();

					Sleep(1);
				}
			}

			scene->End();

			graphics3D->Shutdown();

			ReleaseGraphics3D(graphics3D);

			this->FacePlant();
		}

		void Application::FacePlant() {
			if (!Window::Instance().EndWindow()) {
				Window::LastErrorToConsole();
				Window::LastErrorToMessageBox();
			}

			g_AppHandle = nullptr;
		}


		Application::~Application() { }
	}
}