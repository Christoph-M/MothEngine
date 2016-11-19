#include "include\Fatherload\TestScene.h"

#include <cstdio>

#define MOTH_PREFIX
#include <Moth.Core\Moth.Core.h>


namespace Fatherload {
	void TestScene::Begin() {
		MothCore::Input::Instance()->Subscribe('D', false, this);
	}

	void TestScene::Update() {
		
	}

	void TestScene::Draw2D() {

	}

	void TestScene::Draw3D() {

	}

	void TestScene::End() {
		MothCore::Input::Instance()->Unsubscribe('D', this);
	}

	void TestScene::OnInput(Moth_Int32 vKey) {
		wprintf(L"Key Pressed\n");
	}

	void TestScene::OnInputDown(Moth_Int32 vKey) {
		wprintf(L"Key Down\n");
	}

	void TestScene::OnInputUp(Moth_Int32 vKey) {
		wprintf(L"Key Up\n");
	}

	void TestScene::OnInputToggle(Moth_Int32 vKey) {
		wprintf(L"Key Toggled\n");
	}
}