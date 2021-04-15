#pragma once

#include "Engine/API.h"
#include "Component.h"
#include <vector>
#include <typeinfo>

namespace engine {

	class ENGINE_API GameObject
	{
	public:
		GameObject();
		~GameObject();
		virtual void Update();

		void AddComponent(Component* component);
		template <typename T> T* GetComponent();

	protected:
		std::vector<Component*>* m_Components;
	};

	// GetComponent<T> implementation
	template <typename T>
	T* GameObject::GetComponent()
	{
		for (size_t i = 0; i < m_Components->size(); i++)
			if (typeid(T).name() == m_Components->operator[](i)->GetType())
				return static_cast<T*>(m_Components->operator[](i));

		return nullptr;
	}

}