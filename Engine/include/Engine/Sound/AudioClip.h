#pragma once

#include "Engine/API.h"
#include <cstdint>

namespace engine {

	class ENGINE_API AudioClip
	{
	public:
		AudioClip();
		AudioClip(const char* audioFile);
		void SetAudioFile(const char* audioFile);
		uint32_t GetBufferID();

	private:
		uint32_t m_Buffer;
	};

}