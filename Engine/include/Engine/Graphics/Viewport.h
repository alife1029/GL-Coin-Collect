#pragma once

#include "Engine/API.h"

namespace engine {

	class ENGINE_API Viewport
	{
	public:
		Viewport(int w, int h);
		void Update(int width, int height);
	private:
		int m_Width;
		int m_Height;
		float m_Aspect;
	};

}