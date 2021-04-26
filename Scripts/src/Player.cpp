#include "Player.h"
#include <typeinfo>

using namespace engine;

void Player::OnAttach()
{
	m_Transform = GetGameObject()->GetComponent<Transform>();
	m_Animator = GetGameObject()->GetComponent<Animator>();
}
void Player::Update() 
{
	// Move Player
	m_Direction = 0.0f;
	if (Input::GetKey(ENGINE_KEY_A) || Input::GetKey(ENGINE_KEY_LEFT))
	{
		m_Direction = -1.0f;
		m_Transform->SetScale(-1.0f, 1.0f);
		
		if (m_MovementState == 0) 
		{
			m_Animator->ActivateAnimation(1);
			m_MovementState = 1;
		}
	}
	else if (Input::GetKey(ENGINE_KEY_D) || Input::GetKey(ENGINE_KEY_RIGHT))
	{
		m_Direction = 1.0f;
		m_Transform->SetScale(1.0f, 1.0f);

		if (m_MovementState == 0)
		{
			m_Animator->ActivateAnimation(1);
			m_MovementState = 1;
		}
	}
	else if (m_MovementState) 
	{
		m_MovementState = 0;
		m_Animator->ActivateAnimation(0);
	}

	m_Transform->Move(m_Direction * m_Speed * Time::GetDeltaTime(), 0.0f);

	if (m_Transform->GetPosition().x > 1.0f)
		m_Transform->SetPosition(-1.0f, m_Transform->GetPosition().y);
	else if (m_Transform->GetPosition().x < -1.0f)
		m_Transform->SetPosition(1.0f, m_Transform->GetPosition().y);
}

void Player::IncreaseScore(const uint32_t amount)
{
	m_Score += amount;
	m_Speed += powf(amount / 50.0f, 2.0f);
	std::string scoreStr = "Score: " + std::to_string(m_Score);
	m_TextRenderer->SetText(scoreStr.c_str());
}

void Player::DecreaseScore(const uint32_t amount)
{
	m_Score -= amount;
	std::string scoreStr = "Score: " + std::to_string(m_Score);
	m_TextRenderer->SetText(scoreStr.c_str());
}

std::string Player::GetType()
{
	return typeid(*this).name();
}