#include "Engine/File.h"
#include <fstream>
#include <iostream>

namespace engine {

	std::string File::ReadFile(const char* fileName)
	{
		std::ifstream stream(fileName);
		std::string readedData;

		if (stream.is_open())
		{
			char readedChar;
			while ((readedChar = stream.get()) != EOF)
				readedData += readedChar;
		}

		stream.close();

		return readedData;
	}

}