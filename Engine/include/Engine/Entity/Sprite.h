#pragma once

#include "Engine/API.h"
#include "GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/SpriteRenderer.h"

namespace engine {

	class ENGINE_API Sprite : public GameObject
	{
	public:
		Sprite(const char* imageName, const Vector2& size);
		void Update() override;
	};

}