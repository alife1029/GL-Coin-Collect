#include "Coin.h"
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#include "Player.h"

using namespace engine;

void Coin::OnAttach()
{
	m_Transform = GetGameObject()->GetComponent<Transform>();
	srand(static_cast<uint32_t>(time(0)));
	Reset();
}

void Coin::Update()
{
	m_Transform->Move(0.0f, -m_Speed * Time::GetDeltaTime());
	if (m_Transform->GetPosition().y < -0.55f)
		Reset();

	// Player & Coin Collision Control
	Transform* playerTransform = m_Player->GetComponent<Transform>();
	Vector2 playerPos = playerTransform->GetPosition();
	Vector2 playerSize = playerTransform->GetSize();

	bool colliding;
	colliding = (playerPos.x + playerSize.x / 2.0f > m_Transform->GetPosition().x - m_Transform->GetSize().x / 2.0f + 0.05f) &&
				(playerPos.x - playerSize.x / 2.0f < m_Transform->GetPosition().x + m_Transform->GetSize().x / 2.0f - 0.05f) &&
				(playerPos.y + playerSize.y / 2.0f > m_Transform->GetPosition().y - m_Transform->GetSize().y / 2.0f + 0.11f);
	if (colliding)
	{
		m_Player->GetComponent<Player>()->IncreaseScore();
		Reset();		
	}
}

void Coin::Reset()
{
	m_Transform->SetPosition((rand() % (35) - 17) / 20.0f, 1.0f);
}


std::string Coin::GetType()
{
	return typeid(*this).name();
}
