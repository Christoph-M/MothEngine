#pragma once

#include <Windows.h>
#include <list>
#include <map>

#include "Moth.Core.Datatypes.h"


namespace Moth {
	namespace Core {
		class Input {
		public:
			void Subscribe(Moth_Int32, bool, class IObserverInput*);
			bool Unsubscribe(Moth_Int32, class IObserverInput*);

			void CheckInput();

		private:
			struct Subscriber {
				class IObserverInput* observer;
				bool onToggle;
			};

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