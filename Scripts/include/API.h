#pragma once

#ifdef _WIN32
	#ifdef SCRIPT_BUILD_SHARED_LIB
		#define SCRIPT_API __declspec(dllexport)
	#else
		#define SCRIPT_API __declspec(dllimport)
	#endif	
#endif