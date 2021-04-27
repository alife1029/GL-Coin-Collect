#include "Engine/Graphics/FontManager.h"
#include "Engine/Exception/Exception.h"
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace engine {

	std::map<std::string, FontFamily*> FontManager::m_LoadedFonts = std::map<std::string, FontFamily*>();

	FontFamily* FontManager::LoadFont(const std::string& fontFile)
	{
		if (!m_LoadedFonts.count(fontFile))
		{
			FontFamily* newFont = new FontFamily();

			// Initialize freetype
			FT_Library ft;
			if (FT_Init_FreeType(&ft))
				throw EngineException("Failed to initialize Freetype Library!");
			
			// Load Font Family
			FT_Face face;
			if (FT_New_Face(ft, fontFile.c_str(), 0, &face))
				throw EngineException("Failed to load font!");

			// Read all characters
			FT_Set_Pixel_Sizes(face, 0, 64);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			for (unsigned char c = 0; c < 255; c++)
			{
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
					continue;

				// Generate texture
				uint32_t texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// Store character
				Character newCharacter = {
					texture,
					{ face->glyph->bitmap.width, face->glyph->bitmap.rows },
					{ face->glyph->bitmap_left, face->glyph->bitmap_top },
					static_cast<uint32_t>(face->glyph->advance.x)
				};
				newFont->Characters.insert(std::pair<char, Character>(c, newCharacter));
				if (newCharacter.Size.y > newFont->fontSize)
					newFont->fontSize = newCharacter.Size.y;
			}
			
			glBindTexture(GL_TEXTURE_2D, 0);

			// Shutdown Freetype
			FT_Done_Face(face);
			FT_Done_FreeType(ft);

			m_LoadedFonts.insert(std::pair<std::string, FontFamily*>(fontFile, newFont));
		}

		return m_LoadedFonts[fontFile];
	}

}