#pragma once

#include "Engine/API.h"
#include "Engine/Application/Application.h"

namespace engine {

	class ENGINE_API Input
	{
	public:
		static bool GetKey(int keycode);
	private:
		static GLFWwindow* m_Window;

		friend Application;
	};

}