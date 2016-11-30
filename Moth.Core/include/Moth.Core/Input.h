#pragma once

#include <Windows.h>
#include <list>
#include <map>

#include "Moth.Core.Datatypes.h"


namespace Moth {
	namespace Core {
		enum EKeyState {
			KeyPressed,
			KeyDown,
			KeyUp,
			KeyToggled
		};

		class Input {
			friend class Application;

		public:
			void Subscribe(Moth_Int32, bool, class IObserverInput*);
			bool Unsubscribe(Moth_Int32, class IObserverInput*);

			bool GetKeyDown(Moth_Int32);
			static bool GetKey(Moth_Int32);
			bool GetKeyUp(Moth_Int32);
			static bool GetKeyToggle(Moth_Int32);

		private:
			struct Subscriber {
				class IObserverInput* observer;
				bool onToggle;
			};

		private:
			void CheckInput();

		private:
			std::map<Moth_Int32, std::list<Subscriber>> inputEvents_;

			bool keyPressedLastCall_[0xFF];


		// ******************************** Singleton ********************************
		public:
			static Input* Instance() {
				static CGuard g;
				if (!instance_) instance_ = new Input();
				return instance_;
			}

			Input(const Input&) = delete;
			void operator= (const Input&) = delete;

		private:
			class CGuard {
			public:
				~CGuard() {
					if (Input::instance_) {
						delete(Input::instance_);
						Input::instance_ = nullptr;
					}
				}
			};

		private:
			Input() : keyPressedLastCall_{ false } { };
			~Input() { };

		private:
			static Input* instance_;
		};
	}
}