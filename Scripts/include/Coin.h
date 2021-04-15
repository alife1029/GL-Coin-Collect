#pragma once

#include "API.h"
#include <Engine.h>

class SCRIPT_API Coin : public engine::Component
{
public:
	void OnAttach() override;
	void Update() override;
	std::string GetType() override;
private:
	void Reset();
public:
	engine::GameObject* m_Player = nullptr;
private:
	engine::Transform* m_Transform;
	float m_Speed = 0.8f;
};