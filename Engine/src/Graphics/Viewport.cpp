#include "Engine/Graphics/Viewport.h"
#include <glad/glad.h>
#include <cmath>

namespace engine {

	Viewport::Viewport(int w, int h)
	{
		m_Width = w;
		m_Height = h;
		m_Aspect = static_cast<float>(w) / static_cast<float>(h);
	}

	void Viewport::Update(int width, int height)
	{
		int x, y, w, h;
		float newAspect = static_cast<float>(width) / static_cast<float>(height);

		if (newAspect >= m_Aspect) 
		{
			w = static_cast<int>(height * m_Aspect);
			h = height;
			x = static_cast<int>((width - w) / 2.0f);
			y = 0;
		} 
		else
		{
			w = width;
			h = static_cast<int>(width * pow(m_Aspect, -1.0));
			x = 0;
			y = static_cast<int>((height - h) / 2.0f);
		}

		glViewport(x, y, w, h);
	}

}