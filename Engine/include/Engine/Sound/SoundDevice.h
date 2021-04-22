#pragma once

#include <AL/alc.h>

namespace engine {

	class SoundDevice
	{
	public:
		static SoundDevice* Get();
	private:
		SoundDevice();
		~SoundDevice();
		static SoundDevice* m_Instance;

		ALCdevice* m_ALCDevice;
		ALCcontext* m_ALCContext;
	};

}