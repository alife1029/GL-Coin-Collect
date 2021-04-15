#include "Engine/Entity/GameObject.h"

namespace engine {

	GameObject::GameObject()
	{
		m_Components = new std::vector<Component*>();
	}
	GameObject::~GameObject()
	{
		for (size_t i = 0; i < m_Components->size(); i++)
			delete m_Components->operator[](i);
		delete m_Components;
	}

	void GameObject::Update()
	{
		for (size_t i = 0; i < m_Components->size(); i++)
			m_Components->operator[](i)->Update();
	}

	void GameObject::AddComponent(Component* c)
	{
		m_Components->push_back(c);
		c->m_GameObject = this;
		c->OnAttach();
	}

}