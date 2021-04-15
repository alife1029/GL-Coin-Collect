#pragma once

#include "Engine/API.h"
#include "Engine/Entity/Component.h"
#include "SpriteRenderer.h"
#include <vector>
#include <cstdint>
#include <map>

namespace engine {

	struct AnimationFrame
	{
		char texture[64];
		float duration;
	};

	struct Animation
	{
		uint8_t framesLength = 0;
		std::vector<AnimationFrame> frames = std::vector<AnimationFrame>();
	};

	class ENGINE_API Animator : public Component
	{
	public:
		Animator();
		void OnAttach() override;
		void Update() override;
		std::string GetType() override;
		void AddAnimation(const char* anim);
		void ActivateAnimation(const std::string& animPath);
		void ActivateAnimation(uint8_t index);
	private:
		std::vector<Animation>* m_Animations;
		std::map<std::string, uint8_t> m_AnimMap;
		uint8_t m_CurrentAnim;
		uint8_t m_Currentframe;
		float m_RemainingTimeToNextFrame;
		SpriteRenderer* m_Renderer;
	};

}