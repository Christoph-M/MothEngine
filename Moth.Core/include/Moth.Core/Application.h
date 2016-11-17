#pragma once

#include <Windows.h>


namespace Moth {
	namespace Core {
		class Application {
		public:
			Application();


			void Run(struct IScene*);
			void FacePlant();


			~Application();

		private:
			bool running_;
			MSG messages_;
		};
	}
}