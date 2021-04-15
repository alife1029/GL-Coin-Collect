#pragma once

namespace engine {

	struct ImageData
	{
		int width, height, nrChannels;
		unsigned char* pixels;

		static ImageData LoadImage(const char* imageName);
		static void UnloadImage(const ImageData& image);
	};

}