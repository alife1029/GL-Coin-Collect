#include "Engine/Components/Transform.h"
#include <typeinfo>

namespace engine {

	Transform::Transform()
	{
		m_Position = { 0.0f, 0.0f };
		m_Size = { 1.0f, 1.0f };
		m_Scale = { 1.0f, 1.0f };
	}

	// Position transformations
	void Transform::Move(float x, float y)
	{
		m_Position.x += x;
		m_Position.y += y;
	}
	void Transform::Move(const Vector2& amount)
	{
		m_Position.x += amount.x;
		m_Position.y += amount.y;
	}

	// Position setters
	void Transform::SetPosition(float x, float y)
	{
		m_Position = { x, y };
	}
	void Transform::SetPosition(const Vector2& pos)
	{
		m_Position = pos;
	}
	// Position getter
	Vector2 Transform::GetPosition() { return m_Position; }
	
	// Size setters and getters
	void Transform::SetSize(float x, float y)
	{
		m_Size = { x, y };
	}
	void Transform::SetSize(const Vector2& size)
	{
		m_Size = size;
	}
	Vector2 Transform::GetSize() { return m_Size; }

	void Transform::SetScale(float x, float y)
	{
		m_Scale = { x, y };
	}
	void Transform::SetScale(const Vector2& scale)
	{
		m_Scale = scale;
	}
	Vector2 Transform::GetScale() { return m_Scale; }

	std::string Transform::GetType() { return typeid(*this).name(); }

}