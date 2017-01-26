#define MOTH_PREFIX

#include <Moth.Core\Moth.Core.h>
#include <Moth.Math\Moth.Math.h>

#include <cstdio>

#include "include\Fatherload\TestScene.h"


void main() {
	MothCore::Application app;

	MothCore::Window::Description windowDescription = MothCore::Window::Instance().GetDescription();
	wprintf(L"Window size: %ld, %ld\n", windowDescription.width, windowDescription.height);

	MothMath::FVector2 v1 = { 1, 1 };
	MothMath::FVector2 v2 = { 2, 2 };
	
	v1 += v2;
	assert((v1 == MothMath::FVector2 { 3, 3 }));
	v1 -= v2;
	assert((v1 == MothMath::FVector2 { 1, 1 }));
	v1 *= v2;
	assert((v1 == MothMath::FVector2 { 2, 2 }));
	v1 /= v2;
	assert((v1 == MothMath::FVector2 { 1, 1 }));

	MothMath::FMatrix blah = MothMath::FMatrix::Identity();
	blah = blah.Mul(5.0f);
	blah /= blah;
	blah /= blah.m[0];
	assert(blah == MothMath::FMatrix::Identity());

	app.Run(new Fatherload::TestScene());
}