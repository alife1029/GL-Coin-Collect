#include "Engine/Entity/Text.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/TextRenderer.h"

namespace engine {

	Text::Text()
	{
		AddComponent(new Transform());
		AddComponent(new TextRenderer());
	}

	void Text::Update()
	{
		for (size_t i = 0; i < m_Components->size(); i++)
			m_Components->operator[](i)->Update();
	}

}