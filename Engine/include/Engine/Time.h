#pragma once

#include "Engine/API.h"
#include "Engine/Application/Application.h"

namespace engine {

	class ENGINE_API Time
	{
	public:
		static inline double GetDeltaTime() { return currentFrame - lastFrame; }

	protected:
		static void Update();

	private:
		static double lastFrame;
		static double currentFrame;

		friend Application;
	};

}