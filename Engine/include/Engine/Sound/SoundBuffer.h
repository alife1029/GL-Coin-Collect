#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace engine {

	class SoundBuffer
	{
	public:
		static SoundBuffer* Get();

		uint32_t LoadSoundEffect(const std::string& fileName);

	private:
		SoundBuffer();
		~SoundBuffer();

		static SoundBuffer* m_Instance;
		std::map<std::string, uint32_t> m_SoundEffects;
	};

}