#pragma once

#include "Window.h"
#include "Input.h"
#include "Application.h"

#ifdef MOTH_PREFIX

#define MothCore ::Moth::Core
#define MothMath ::Moth::Math

#endif

#ifdef MOTH_LIB_EXPORT
	#define MOTHLIB __declspec(dllexport)
#else
	#define MOTHLIB __declspec(dllimport)
#endif
