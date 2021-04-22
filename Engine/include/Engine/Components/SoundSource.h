#pragma once

#include "Engine/API.h"
#include "Engine/Entity/Component.h"
#include "Engine/Sound/AudioClip.h"

namespace engine {

	class ENGINE_API SoundSource : public Component
	{
	public:
		SoundSource();
		~SoundSource();

		void Play(AudioClip* clipToPlay);
		
		void OnAttach() override;
		void Update() override;
		std::string GetType() override;

	private:
		uint32_t m_Source = 0;
		float m_Pitch = 1.0f;
		float m_Gain = 1.0f;
		float m_Position[3] = { 0, 0, 0 };
		float m_Velocity[3] = { 0, 0, 0 };
		bool m_LoopSound = false;
		uint32_t m_Buffer = 0;
	};

}