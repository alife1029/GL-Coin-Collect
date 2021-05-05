#pragma once

#ifdef _WIN32
	#ifdef ENGINE_BUILD_SHARED_LIB
		#define ENGINE_API __declspec(dllexport)
	#else	
		#define ENGINE_API __declspec(dllimport)
	#endif
#endif
