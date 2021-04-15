#include "Engine/Entity/Sprite.h"

namespace engine {

	Sprite::Sprite(const char* imageName, const Vector2& size) : GameObject()
	{
		AddComponent(new Transform());
		GetComponent<Transform>()->SetSize(size);

		AddComponent(new SpriteRenderer(imageName));
	}

	void Sprite::Update() 
	{ 
		for (size_t i = 0; i < m_Components->size(); i++)
			m_Components->operator[](i)->Update();
	}

}