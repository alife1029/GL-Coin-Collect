#include "Engine/Entity/Component.h"
#include <typeinfo>

namespace engine {

	void Component::Update() { }
	std::string Component::GetType() { return typeid(*this).name(); }
	GameObject* Component::GetGameObject() { return m_GameObject; }
	void Component::OnAttach() { }

}