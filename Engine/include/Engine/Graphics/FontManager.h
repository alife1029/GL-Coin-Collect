#pragma once

#include "Engine/Math/Vector2Int.h"
#include <cstdint>
#include <map>
#include <string>

namespace engine {

	struct Character
	{
		uint32_t	TextureID; // ID handle of the glyph texture
		Vector2Int	Size;      // Size of glyph
		Vector2Int	Bearing;   // Offset from baseline to left/top of glyph
		uint32_t	Advance;   // Horizontal offset to advance to next glyph
	};

	struct FontFamily
	{
		std::map<char, Character> Characters;
		float fontSize;
	};

	class FontManager
	{
	public:
		static FontFamily* LoadFont(const std::string& fontFile);
	private:
		static std::map<std::string, FontFamily*> m_LoadedFonts;
	};

}