#include "Engine/Exception/Exception.h"

namespace engine {

	EngineException::EngineException()
	{
		m_Data = "[ENGINE] An error occured!";
	}

	EngineException::EngineException(const std::string& message)
	{
		m_Data = "[ENGINE] " + message;
	}

	const char* EngineException::what() const
	{
		return m_Data.c_str();
	}

}