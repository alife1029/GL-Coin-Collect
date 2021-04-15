#include "Engine/Input/Input.h"
#include "Engine/Application/Application.h"
#include <GLFW/glfw3.h>

namespace engine {

	GLFWwindow* Input::m_Window = nullptr;

	bool Input::GetKey(int keycode)
	{
		int state = glfwGetKey(m_Window, keycode);
		if (state == GLFW_PRESS)
			return true;
		return false;
	}

}