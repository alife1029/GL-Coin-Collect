#pragma once

#include "Engine/API.h"

struct GLFWwindow;

namespace engine {

	class ENGINE_API Window
	{
	public:
		Window(unsigned int width, unsigned int height, const char* title, bool fullscreen);
		~Window();

		bool IsOpen();

		GLFWwindow* GetGLFWwindow();
	private:
		GLFWwindow* m_Window;
	};

}