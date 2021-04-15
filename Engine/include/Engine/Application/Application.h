#pragma once

#include "Engine/API.h"
#include "ApplicationConfig.h"
#include "Window.h"

namespace engine {

	class ENGINE_API Application
	{
	public:
		Application(const ApplicationConfig& config);
		virtual ~Application();
		virtual void Update();
		void Run();

	private:
		Window* m_Window;

		friend class EventSystem;
	};

}