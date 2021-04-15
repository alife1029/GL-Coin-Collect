#pragma once

#ifdef SCRIPT_BUILD_DLL
	#define SCRIPT_API __declspec(dllexport)
#else
	#define SCRIPT_API __declspec(dllimport)
#endif