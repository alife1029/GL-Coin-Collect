#include "Engine/Graphics/TextureManager.h"
#include "Engine/Graphics/ImageData.h"
#include <glad/glad.h>

namespace engine {

	std::map<std::string, uint32_t> TextureManager::m_TextureMap = std::map<std::string, uint32_t>();

	uint32_t TextureManager::LoadTexture(const std::string& imageName)
	{
		if (m_TextureMap.count(imageName))
			return m_TextureMap[imageName];

		// Load image
		ImageData loadedImage = ImageData::LoadImage(imageName.c_str());

		// Generate texture
		uint32_t textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedImage.width, loadedImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedImage.pixels);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

		// Unload image
		ImageData::UnloadImage(loadedImage);

		// Add texture to hash table
		m_TextureMap[imageName] = textureID;
		return textureID;
	}

}