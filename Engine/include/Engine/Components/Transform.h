#pragma once

#include "Engine/API.h"
#include "Engine/Entity/Component.h"
#include "Engine/Math/Vector2.h"
#include <string>

namespace engine {

	class ENGINE_API Transform : public Component
	{
	public:
		Transform();

		void Move(float x, float y);
		void Move(const Vector2& amount);

		void SetPosition(float x, float y);
		void SetPosition(const Vector2& pos);

		Vector2 GetPosition();

		void SetSize(float x, float y);
		void SetSize(const Vector2& size);
		Vector2 GetSize();

		void SetScale(float x, float y);
		void SetScale(const Vector2& scale);
		Vector2 GetScale();

		std::string GetType() override;

	private:
		Vector2 m_Position;
		Vector2 m_Size;
		Vector2 m_Scale;
	};

}