#pragma once

#include "API.h"
#include <Engine.h>

class SCRIPT_API Collectable : public engine::Component
{
public:
	void OnAttach() override;
	void Update() override;
	std::string GetType() override;
private:
	void Reset();
public:
	engine::GameObject* m_Player = nullptr;
	
	/*
		-2 = Poop
		 1 = Bronze
		 3 = Silver
		 5 = Gold
	*/
	char type = 0;

	engine::AudioClip* m_CoinAudio = nullptr;
	engine::AudioClip* m_PoopAudio = nullptr;
private:
	engine::SoundSource* m_SoundSource = nullptr;
	engine::Transform* m_Transform = nullptr;
	float m_Speed = 1.0f;
};