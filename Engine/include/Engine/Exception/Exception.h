#pragma once

#include "Engine/API.h"
#include <exception>
#include <string>

namespace engine {

	class ENGINE_API EngineException : public std::exception
	{
	public:
		EngineException();
		EngineException(const std::string& message);
		const char* what() const override;
	private:
		std::string m_Data;
	};

}