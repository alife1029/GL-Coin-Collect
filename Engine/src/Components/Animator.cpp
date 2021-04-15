#include "Engine/Components/Animator.h"
#include "Engine/Time.h"
#include "Engine/Entity/GameObject.h"
#include <fstream>
#include <typeinfo>

namespace engine {

	Animation LoadAnimation(const char* fileName)
	{
		Animation anim;
		std::ifstream stream(fileName, std::ifstream::binary);

		// Deserialize frames length
		stream.read((char*)&anim.framesLength, sizeof(uint8_t));
		for (uint8_t i = 0; i < anim.framesLength; i++)
		{
			AnimationFrame loadedFrame;
			stream.read((char*)&loadedFrame, sizeof(AnimationFrame));
			anim.frames.push_back(loadedFrame);
		}

		stream.close();
		return anim;
	}

	Animator::Animator()
	{
		m_Animations = new std::vector<Animation>();
		m_CurrentAnim = 0;
		m_Currentframe = 0;
		m_RemainingTimeToNextFrame = 0.0f;
		m_Renderer = nullptr;
	}

	void Animator::OnAttach() 
	{ 
		m_Renderer = GetGameObject()->GetComponent<SpriteRenderer>();
		if (m_Renderer == nullptr)
			throw "You must attach Sprite Renderer before than Animator!";
	}
	
	void Animator::Update() 
	{
		if (m_Animations->size() > 0)
		{
			Animation current = m_Animations->operator[](m_CurrentAnim);
			m_Renderer->SetImage(current.frames[m_Currentframe].texture);
			m_RemainingTimeToNextFrame -= static_cast<float>(Time::GetDeltaTime());
			if (m_RemainingTimeToNextFrame <= 0.0f)
			{
				// If end of the animation, run back
				++m_Currentframe;
				if (m_Currentframe >= current.framesLength)
					m_Currentframe = 0;

				m_RemainingTimeToNextFrame = current.frames[m_Currentframe].duration;
			}
		}
	}

	void Animator::AddAnimation(const char* anim)
	{
		m_Animations->push_back(LoadAnimation(anim));
		m_AnimMap[std::string(anim)] = m_Animations->size() - 1;
	}

	void Animator::ActivateAnimation(const std::string& animPath)
	{
		m_CurrentAnim = m_AnimMap[animPath];
		m_Currentframe = 0;
		m_RemainingTimeToNextFrame = m_RemainingTimeToNextFrame = m_Animations->operator[](m_CurrentAnim).frames[m_Currentframe].duration;
	}
	void Animator::ActivateAnimation(uint8_t index)
	{
		m_CurrentAnim = index;
		m_Currentframe = 0;
		m_RemainingTimeToNextFrame = m_RemainingTimeToNextFrame = m_Animations->operator[](m_CurrentAnim).frames[m_Currentframe].duration;
	}
	
	std::string Animator::GetType() { return typeid(*this).name(); }

}