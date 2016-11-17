#include "include/Moth.Core/Window.h"

#include <cstdio>


namespace Moth {
	namespace Core {
		bool Window::MakeWindow() {
			WNDCLASSEX wndClassEx = { 0 };
				wndClassEx.cbSize = sizeof(wndClassEx);
				wndClassEx.style = CS_DROPSHADOW;
				wndClassEx.lpfnWndProc = WindowProcedure;
				wndClassEx.cbClsExtra = NULL;
				wndClassEx.hInstance = GetModuleHandle(NULL);
				wndClassEx.hIcon = LoadIcon(0, IDI_EXCLAMATION);
				wndClassEx.hCursor = LoadCursor(0, IDC_ARROW);
				wndClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW;
				wndClassEx.lpszMenuName = NULL;
				wndClassEx.lpszClassName = L"MothEngine";
				wndClassEx.hIconSm = LoadIcon(0, IDI_EXCLAMATION);

			if (!RegisterClassEx(&wndClassEx)) return false;

			Moth_UInt32 dStyle = WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

			hwnd_ = CreateWindowEx(0, wndClassEx.lpszClassName, L"Moth Engine", dStyle,
								   CW_USEDEFAULT, CW_USEDEFAULT, 500, 200, HWND_DESKTOP, NULL, wndClassEx.hInstance, NULL);
			if (!hwnd_) return false;

			if (ShowWindow(hwnd_, SW_SHOW)) return false;

			this->RetrieveDimensions();

			return true;
		}

		void Window::LastErrorToConsole() {
			Moth_UInt32 error = GetLastError();
			Moth_Char16 buffer[1024] = L"";
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, NULL, buffer, 1024, NULL);
			wprintf(L"%s", buffer);
		}

		void Window::LastErrorToMessageBox() {
			Moth_UInt32 error = GetLastError();
			Moth_Char16 buffer[1024] = L"";
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, NULL, buffer, 1024, NULL);
			MessageBox(nullptr, buffer, L"Error", MB_OK | MB_ICONERROR);
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
