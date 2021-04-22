#include "Engine/Application/Application.h"
#include "Engine/Sound/SoundDevice.h"
#include "Engine/Input/Input.h"
#include "Engine/Time.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {

	Application::Application(const ApplicationConfig& config)
	{
		m_Window = new Window(config.width, config.height, config.title, config.fullscreen);
		Input::m_Window = m_Window->GetGLFWwindow();
		
		// Initialize Sound Device
		m_SoundDevice = SoundDevice::Get();
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Update() { }
	void Application::Run()
	{
		while (m_Window->IsOpen())
		{
			glClear(GL_COLOR_BUFFER_BIT);
			Update();
			glfwSwapBuffers(m_Window->GetGLFWwindow());
			glfwPollEvents();

			Time::Update();
		}
	}

}