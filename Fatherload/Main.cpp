#define MOTH_PREFIX

#include <Moth.Core\Moth.Core.h>

#include <cstdio>


void main() {
	MothCore::Application app = MothCore::Application();

	MothCore::Window::Description windowDescription = MothCore::Window::Instance()->GetDescription();
	wprintf(L"Window size: %ld, %ld\n", windowDescription.width, windowDescription.height);

	app.Run();
}