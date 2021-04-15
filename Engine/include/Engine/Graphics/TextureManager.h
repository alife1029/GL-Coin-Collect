#pragma once

#include <cstdint>
#include <string>
#include <map>

namespace engine {

	class TextureManager
	{
	public:
		static uint32_t LoadTexture(const std::string& imageName);
	private:
		static std::map<std::string, uint32_t> m_TextureMap;
	};

}