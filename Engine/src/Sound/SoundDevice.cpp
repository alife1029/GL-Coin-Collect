#include "Engine/Sound/SoundDevice.h"
#include <AL/al.h>
#include <stdio.h>

namespace engine {

	SoundDevice* SoundDevice::m_Instance = nullptr;

	SoundDevice* SoundDevice::Get()
	{
		if (m_Instance == nullptr)
			m_Instance = new SoundDevice();

		return m_Instance;
	}

	SoundDevice::SoundDevice() 
	{ 
		m_ALCDevice = alcOpenDevice(nullptr); // nullptr = default device
		if (!m_ALCDevice)
			throw "Failed to open sound device!";

		m_ALCContext = alcCreateContext(m_ALCDevice, nullptr); // Create context
		if (!m_ALCContext)
			throw "Failed to set sound context!";

		if (!alcMakeContextCurrent(m_ALCContext)) // Make context current
			throw "Failed to make context current!";
	}

	SoundDevice::~SoundDevice()
	{
		if (!alcMakeContextCurrent(nullptr))
			throw "Failed to remove current context!";

		alcDestroyContext(m_ALCContext);
		if (m_ALCContext)
			throw "Failed to destroy OpenAL sound context!";

		if (!alcCloseDevice(m_ALCDevice))
			throw "Failed to close sound device!";
	}

}