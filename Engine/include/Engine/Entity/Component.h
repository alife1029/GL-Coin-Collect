#pragma once

#include "Engine/API.h"
#include <string>

namespace engine {

	class GameObject;

	class ENGINE_API Component
	{
	public:
		virtual void OnAttach();
		virtual void Update();
		virtual std::string GetType();

	private:
		GameObject* m_GameObject = nullptr;

	protected:
		GameObject* GetGameObject();

		friend GameObject;
	};

}