#pragma once

#include <Windows.h>


namespace Moth {
	namespace Core {
		LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

		class Window {
		public:
			struct Description {
				LONG x, y, right, bottom, width, height;
			};

		public:
			bool MakeWindow();

			HWND GetWindow() { return hwnd_; }
			const Description& GetDescription() { return windowDescription_; }

		private:
			void RetrieveDimensions();

		private:
			HWND hwnd_;

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
			Window() { };
			~Window() { };

		private:
			static Window* instance_;
		};
	}
}