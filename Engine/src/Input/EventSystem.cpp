#include "Engine/Input/EventSystem.h"
#include "Engine/Application/Application.h"
#include <GLFW/glfw3.h>

namespace engine {

	// For glfw events
	class GLFWevents
	{
	public:
		static void SetEventListener(EventSystem* eventSystem);

		// GLFW callbacks
		static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
	private:
		static EventSystem* m_EventSystem;
	};

	// Implemetation of glfw events
	EventSystem* GLFWevents::m_EventSystem = nullptr;
	void GLFWevents::SetEventListener(EventSystem* eventSystem) { m_EventSystem = eventSystem; }
	void GLFWevents::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			m_EventSystem->Keydown(key);
		else if (action == GLFW_RELEASE)
			m_EventSystem->Keyup(key);
	}
	void GLFWevents::glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		m_EventSystem->Resize(width, height);
	}





	// Implementation of Event System
	void EventSystem::SetEventListener(Application* listener)
	{
		GLFWevents::SetEventListener(this);

		// Set callbacks
		glfwSetKeyCallback(listener->m_Window->GetGLFWwindow(), GLFWevents::glfw_key_callback);
		glfwSetFramebufferSizeCallback(listener->m_Window->GetGLFWwindow(), GLFWevents::glfw_framebuffer_size_callback);
	}

	// Implementation of callbacks
	void EventSystem::Resize(int width, int height) { }
	void EventSystem::Keydown(int keycode) { }
	void EventSystem::Keyup(int keycode) { }

}