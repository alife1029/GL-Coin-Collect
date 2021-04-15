#include "Engine/Graphics/ImageData.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace engine {

	ImageData ImageData::LoadImage(const char* fileName)
	{
		ImageData loadedImage;
		stbi_set_flip_vertically_on_load(true);
		loadedImage.pixels = stbi_load(fileName, &loadedImage.width, &loadedImage.height, &loadedImage.nrChannels, STBI_rgb_alpha);
		return loadedImage;
	}

	void ImageData::UnloadImage(const ImageData& image)
	{
		stbi_image_free(image.pixels);
	}

}