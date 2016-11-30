#include "include\Moth.Core\Window.h"

#include <cstdio>

#include "include\Moth.Core\GraphicsSettings.h"


namespace Moth {
	namespace Core {
		bool Window::MakeWindow() {
			DEVMODE dmScreenSettings = { 0 };
			int posX, posY, screenWidth, screenHeight;

			hInstance_ = GetModuleHandle(NULL);
			className_ = L"MothEngine";

			WNDCLASSEX wndClassEx = { 0 };
				wndClassEx.cbSize = sizeof(wndClassEx);
				wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
				wndClassEx.lpfnWndProc = WindowProcedure;
				wndClassEx.cbClsExtra = NULL;
				wndClassEx.cbWndExtra = NULL;
				wndClassEx.hInstance = hInstance_;
				wndClassEx.hIcon = LoadIcon(0, IDI_EXCLAMATION);
				wndClassEx.hCursor = LoadCursor(0, IDC_ARROW);
				wndClassEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
				wndClassEx.lpszMenuName = NULL;
				wndClassEx.lpszClassName = className_;
				wndClassEx.hIconSm = LoadIcon(0, IDI_EXCLAMATION);

			if (!RegisterClassEx(&wndClassEx)) return false;

			screenWidth = GetSystemMetrics(SM_CXSCREEN);
			screenHeight = GetSystemMetrics(SM_CYSCREEN);
			Moth_UInt32 dStyle = 0;

			if (FULL_SCREEN) {
				dmScreenSettings.dmSize = sizeof(dmScreenSettings);
				dmScreenSettings.dmPelsWidth = screenWidth;
				dmScreenSettings.dmPelsHeight = screenHeight;
				dmScreenSettings.dmBitsPerPel = 32;
				dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				dStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;

				ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

				posX = 0;
				posY = 0;
			} else {
				dStyle = WS_SYSMENU | WS_MINIMIZEBOX;

				screenWidth = 1280;
				screenHeight = 720;
				posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
				posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
			}

			hwnd_ = CreateWindowEx(0, wndClassEx.lpszClassName, L"Moth Engine", dStyle,
								   posX, posY, screenWidth, screenHeight, HWND_DESKTOP, NULL, wndClassEx.hInstance, NULL);
			if (!hwnd_) return false;

			if (ShowWindow(hwnd_, SW_SHOW)) return false;
			if (!SetForegroundWindow(hwnd_)) return false;
			if (!SetFocus(hwnd_)) return false;

			ShowCursor(false);

			this->RetrieveDimensions();
			wprintf(L"Screen Size: %d, %d\n", screenWidth, screenHeight);

			return true;
		}

		bool Window::EndWindow() {
			ShowCursor(true);
			if (FULL_SCREEN) ChangeDisplaySettings(NULL, 0);

			if (!DestroyWindow(hwnd_)) return false;
			hwnd_ = NULL;

			if (!UnregisterClass(className_, hInstance_)) return false;
			hInstance_ = NULL;

			return true;
		}


		void Window::LastErrorToConsole() {
			Moth_UInt32 error = GetLastError();
			Moth_Char16 buffer[1024] = L"";
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, NULL, buffer, 1024, NULL);
			wprintf(L"%ws\n", buffer);
		#ifdef _DEBUG
			DebugBreak();
		#endif
		}

		void Window::LastErrorToMessageBox() {
			Moth_UInt32 error = GetLastError();
			Moth_Char16 buffer[1024] = L"";
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, NULL, buffer, 1024, NULL);
			MessageBox(nullptr, buffer, L"Error", MB_OK | MB_ICONERROR);
		#ifdef _DEBUG
			DebugBreak();
		#endif
		}

		void Window::LogToConsole(Moth_WString buffer, bool brk) {
			wprintf(L"%ws\n", buffer);
		#ifdef _DEBUG
			if (brk) DebugBreak();
		#endif
		}

		void Window::LogToMessageBox(Moth_WString buffer) {
			Moth_Char16 b[1024] = L"";
			_snwprintf_s(b, 1024, L"%ws\n\nPress Yes to debug, No to continue.", buffer);
			int result = MessageBox(nullptr, b, L"Notice", MB_YESNO | MB_DEFBUTTON1 | MB_ICONEXCLAMATION);
		#ifdef _DEBUG
			if (result == IDYES) DebugBreak();
		#endif
		}

		void Window::RetrieveDimensions() {
			windowDescription_ = { 0 };
			RECT dim = { 0 };
			GetWindowRect(hwnd_, &dim);

			windowDescription_.x	  = dim.left;
			windowDescription_.y	  = dim.top;
			windowDescription_.right  = dim.right;
			windowDescription_.bottom = dim.bottom;
			windowDescription_.width  = dim.right  - dim.left;
			windowDescription_.height = dim.bottom - dim.top;
		}

		Window* Window::instance_ = 0;
	}
}
