#include "Engine/Time.h"
#include <GLFW/glfw3.h>

namespace engine {

	double Time::currentFrame = 0.0;
	double Time::lastFrame = 0.0;

	void Time::Update()
	{
		lastFrame = currentFrame;
		currentFrame = glfwGetTime();
	}

}