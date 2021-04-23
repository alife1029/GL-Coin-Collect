#include "Engine/Application/Window.h"
#include "Engine/Exception/Exception.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {

	Window::Window(unsigned int width, unsigned int height, const char* title, bool fullscreen)
	{
		if (!glfwInit())
			throw EngineException("Failed to initialize GLFW!");

		m_Window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			throw EngineException("Failed to create window!");
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		// Load GL
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw EngineException("Failed to load GL!");

		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::IsOpen()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	GLFWwindow* Window::GetGLFWwindow() { return m_Window; }

}