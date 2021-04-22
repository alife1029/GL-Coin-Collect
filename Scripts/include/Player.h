#pragma once

#include <Engine.h>
#include "API.h"

class SCRIPT_API Player : public engine::Component
{
public:
	void OnAttach() override;
	void Update() override;
	void IncreaseScore();
	std::string GetType() override;
public:
	engine::TextRenderer* m_TextRenderer = nullptr;
	engine::AudioClip* m_CoinAudio = nullptr;
private:
	engine::SoundSource* m_SoundSource = nullptr;
	engine::Transform* m_Transform = nullptr;
	engine::Animator* m_Animator = nullptr;
	float m_Speed = 0.9f;
	uint32_t m_Score = 0;
	float m_Direction = 0.0f;
	bool m_MovementState = 0;
};