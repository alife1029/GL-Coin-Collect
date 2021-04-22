#include "Engine/Components/SoundSource.h"
#include <typeinfo>
#include <AL/al.h>

namespace engine {

	SoundSource::SoundSource() { }

	SoundSource::~SoundSource()
	{
		alDeleteSources(1, &m_Source);
	}

	void SoundSource::OnAttach()
	{
		alGenSources(1, &m_Source);
		alSourcef(m_Source, AL_PITCH, m_Pitch);
		alSourcef(m_Source, AL_GAIN, m_Gain);
		alSource3f(m_Source, AL_POSITION, m_Position[0], m_Position[1], m_Position[2]);
		alSource3f(m_Source, AL_VELOCITY, m_Velocity[0], m_Velocity[1], m_Velocity[2]);
		alSourcei(m_Source, AL_LOOPING, m_LoopSound);
		alSourcei(m_Source, AL_BUFFER, m_Buffer);
	}

	void SoundSource::Update() { }

	void SoundSource::Play(AudioClip* clipToPlay)
	{
		if (m_Buffer != clipToPlay->GetBufferID())
		{
			m_Buffer = clipToPlay->GetBufferID();
			alSourcei(m_Source, AL_BUFFER, (ALint)m_Buffer);
		}

		alSourcePlay(m_Source);
	}

	std::string SoundSource::GetType()
	{
		return typeid(*this).name();
	}

}