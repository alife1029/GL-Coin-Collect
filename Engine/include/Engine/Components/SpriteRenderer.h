#pragma once

#include "Engine/API.h"
#include "Engine/Entity/Component.h"

namespace engine {

	class ShaderProgram;

	class ENGINE_API SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		SpriteRenderer(const char* imageName);
		~SpriteRenderer();

		void SetImage(const char* imageName);

		void Update() override;
		std::string GetType() override;

	private:
		void OnAttach() override;

	private:
		ShaderProgram* m_Shader;
		uint32_t m_TexID;
		uint32_t m_VAO;
		uint32_t m_VBO;
		uint32_t m_IBO;
	};

}