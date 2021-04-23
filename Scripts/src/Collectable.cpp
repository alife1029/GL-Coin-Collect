#include "Collectable.h"
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#include "Player.h"

using namespace engine;

void Collectable::OnAttach()
{
	m_Transform = GetGameObject()->GetComponent<Transform>();
	m_SoundSource = GetGameObject()->GetComponent<SoundSource>();
	Reset();
}

void Collectable::Update()
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
		if (type > 0)
		{
			m_SoundSource->Play(m_CoinAudio);
			m_Player->GetComponent<Player>()->IncreaseScore(type);
		}
		else
		{
			m_SoundSource->Play(m_PoopAudio);
			m_Player->GetComponent<Player>()->DecreaseScore(-type);
		}

		Reset();
	}
}

void Collectable::Reset()
{	
	// Set new type
	std::vector<char> types = { -2, 1, 3, 5 };
	type = types[rand() % 4];
	// Set new texture
	switch (type)
	{
	case -2:
		GetGameObject()->GetComponent<SpriteRenderer>()->SetImage("assets/poop.png");
		break;
	case 1:
		GetGameObject()->GetComponent<SpriteRenderer>()->SetImage("assets/coinBronze.png");
		break;
	case 3:
		GetGameObject()->GetComponent<SpriteRenderer>()->SetImage("assets/coinSilver.png");
		break;
	case 5:
		GetGameObject()->GetComponent<SpriteRenderer>()->SetImage("assets/coinGold.png");
		break;
	}

	m_Transform->SetPosition((rand() % (35) - 17) / 20.0f, 1.0f);
	printf("Reset\n");
}


std::string Collectable::GetType()
{
	return typeid(*this).name();
}
