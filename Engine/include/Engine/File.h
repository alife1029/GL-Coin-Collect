#pragma once

#include <string>

namespace engine {

	class File
	{
	public:
		static std::string ReadFile(const char* fileName);
	};

}