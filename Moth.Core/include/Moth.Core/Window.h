#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Moth.Core.Datatypes.h"


namespace Moth {
	namespace Core {
		LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

		class Window {
		public:
			struct Description {
				Moth_Int32 x, y, right, bottom, width, height;
			};

		public:
			bool MakeWindow();
			bool EndWindow();

			static void LastErrorToConsole();
			static void LastErrorToMessageBox();
			static void LogToConsole(Moth_WString, bool brk = false);
			static void LogToMessageBox(Moth_WString);

			HWND GetWindow() const { return hwnd_; }
			const Description& GetDescription() const { return windowDescription_; }

		private:
			void RetrieveDimensions();

		private:
			HWND hwnd_;
			Moth_WString className_;
			HINSTANCE hInstance_;

			Description windowDescription_;


		// ******************************** Singleton ********************************
		public:
			static Window* Instance() {
				static CGuard g;
				if (!instance_) instance_ = new Window();
				return instance_;
			}

			Window(const Window&) = delete;
			void operator= (const Window&) = delete;

		private:
			class CGuard {
			public:
				~CGuard() {
					if (Window::instance_) {
						delete(Window::instance_);
						Window::instance_ = nullptr;
					}
				}
			};

		private:
			Window() : hwnd_(NULL), className_(L""), hInstance_(NULL) { } ;
			~Window() { };

		private:
			static Window* instance_;
		};
	}
}