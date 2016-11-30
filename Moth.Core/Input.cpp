#include "include\Moth.Core\Input.h"

#include "include\Moth.Core\Interfaces\IObserver.h"


namespace Moth {
	namespace Core {
		void Input::Subscribe(Moth_Int32 vKey, bool toggle, IObserverInput* observer) {
			if (inputEvents_.find(vKey) == inputEvents_.end()) {
				inputEvents_.emplace(vKey, std::list<Subscriber>());
			}
			inputEvents_.find(vKey)->second.emplace_back(Subscriber { observer, toggle });
		}

		bool Input::Unsubscribe(Moth_Int32 vKey, IObserverInput* observer) {
			auto element = inputEvents_.find(vKey);
			if (element != inputEvents_.end()) {
				for (std::list<Subscriber>::iterator it = element->second.begin(); it != element->second.end(); ++it) {
					if (it->observer == observer) {
						element->second.erase(it);
						return true;
					}
				}
			}
			return false;
		}

		bool Input::GetKeyDown(Moth_Int32 vKey) {
			return GetKeyState(vKey) < 0 && !keyPressedLastCall_[vKey];
		}

		bool Input::GetKey(Moth_Int32 vKey) {
			return GetKeyState(vKey) < 0;
		}

		bool Input::GetKeyUp(Moth_Int32 vKey) {
			return GetKeyState(vKey) >= 0 && keyPressedLastCall_[vKey];
		}

		bool Input::GetKeyToggle(Moth_Int32 vKey) {
			return GetKeyState(vKey) == 1;
		}



		void Input::CheckInput() {
			for (auto input : inputEvents_) {
				Moth_Int16 keyState = GetKeyState(input.first);

				if (keyState >= 0 && keyPressedLastCall_[input.first]) {
					keyPressedLastCall_[input.first] = false;
					for (Subscriber subscriber : input.second) subscriber.observer->OnInput(input.first, KeyUp);
				} else if (keyState < 0 && !keyPressedLastCall_[input.first]) {
					keyPressedLastCall_[input.first] = true;
					for (Subscriber subscriber : input.second) subscriber.observer->OnInput(input.first, KeyDown);
				} else if (keyState < 0)
					for (Subscriber subscriber : input.second) subscriber.observer->OnInput(input.first, KeyPressed);
				else if (keyState == 1)
					for (Subscriber subscriber : input.second)
						if (subscriber.onToggle)
							subscriber.observer->OnInput(input.first, KeyToggled);
			}
		}

		Input* Input::instance_ = 0;
	}
}
