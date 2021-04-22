#include "Engine/Sound/AudioClip.h"
#include "Engine/Sound/SoundBuffer.h"

namespace engine {

	AudioClip::AudioClip()
	{
		m_Buffer = 0;
	}

	AudioClip::AudioClip(const char* audioFile)
	{
		SetAudioFile(audioFile);
	}

	void AudioClip::SetAudioFile(const char* audioFile)
	{
		m_Buffer = SoundBuffer::Get()->LoadSoundEffect(audioFile);
	}

	uint32_t AudioClip::GetBufferID()
	{
		return m_Buffer;
	}

}