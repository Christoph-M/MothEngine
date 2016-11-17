#include "Window.h"


namespace Moth {
	namespace Core {
		bool Window::MakeWindow() {
			WNDCLASSEX wndClassEx = { 0 };
				wndClassEx.cbSize = sizeof(wndClassEx);
				wndClassEx.style = CS_DROPSHADOW;
				wndClassEx.lpfnWndProc = WindowProcedure;
				wndClassEx.cbClsExtra = NULL;
				wndClassEx.hInstance = GetModuleHandle(NULL);
				wndClassEx.hIcon = (HICON)IDI_EXCLAMATION;
				wndClassEx.hCursor = (HCURSOR)IDC_ARROW;
				wndClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW;
				wndClassEx.lpszMenuName = NULL;
				wndClassEx.lpszClassName = L"MothEngine";
				wndClassEx.hIconSm = (HICON)IDI_EXCLAMATION;

			if (!RegisterClassEx(&wndClassEx)) return false;

			DWORD dStyle = WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

			hwnd_ = CreateWindowEx(0, wndClassEx.lpszClassName, L"Moth Engine", dStyle,
								   CW_USEDEFAULT, CW_USEDEFAULT, 500, 200, HWND_DESKTOP, NULL, wndClassEx.hInstance, NULL);
			if (!hwnd_) return false;

			if (ShowWindow(hwnd_, SW_SHOW)) return false;

			this->RetrieveDimensions();

			return true;
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
	}
}
