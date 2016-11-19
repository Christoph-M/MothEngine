#include "include\Fatherload\TestScene.h"

#include <cstdio>

#define MOTH_PREFIX
#include <Moth.Core\Moth.Core.h>


namespace Fatherload {
	void TestScene::Begin() {
		MothCore::Input::Instance()->Subscribe('D', false, this);
		MothCore::Input::Instance()->Subscribe('A', true, this);
	}

	void TestScene::Update() {
		
	}

	void TestScene::Draw2D() {

	}

	void TestScene::Draw3D() {

	}

	void TestScene::End() {
		MothCore::Input::Instance()->Unsubscribe('D', this);
		MothCore::Input::Instance()->Unsubscribe('A', this);
	}

	void TestScene::OnInput(Moth_Int32 vKey, MothCore::EKeyState keyState) {
		switch (vKey) {
			case 'D':
				switch (keyState) {
					case MothCore::KeyPressed:
						wprintf(L"D Key Pressed\n");
						break;
					case MothCore::KeyDown:
						wprintf(L"D Key Down\n");
						break;
					case MothCore::KeyUp:
						wprintf(L"D Key Up\n");
						break;
					case MothCore::KeyToggled:
						wprintf(L"D Key Toggled\n");
						break;
					default:
						break;
				}
				break;
			case 'A':
				switch (keyState) {
					case MothCore::KeyPressed:
						wprintf(L"A Key Pressed\n");
						break;
					case MothCore::KeyDown:
						wprintf(L"A Key Down\n");
						break;
					case MothCore::KeyUp:
						wprintf(L"A Key Up\n");
						break;
					case MothCore::KeyToggled:
						wprintf(L"A Key Toggled\n");
						break;
					default:
						break;
				}
				break;
		}
	}
}