#pragma once

#include "Engine/API.h"
#include "Engine/Application/Application.h"

namespace engine {

	class ENGINE_API EventSystem
	{
	public:
		void SetEventListener(Application* listener);

		// Callbacks
		virtual void Resize(int width, int height);
		virtual void Keydown(int keycode);
		virtual void Keyup(int keycode);
	};

}