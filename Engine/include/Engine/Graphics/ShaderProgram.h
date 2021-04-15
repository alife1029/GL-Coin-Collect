#pragma once

#include "Engine/API.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/Matrix3.h"
#include <cstdint>

namespace engine {

	class ENGINE_API ShaderProgram
	{
	public:
		ShaderProgram(const char* vs, const char* fs);
		~ShaderProgram();
		void Use();
		uint32_t GetRendererID();

		// Uniforms
		void SetUniformVec2(const char* varName, const Vector2& val);
		void SetUniformMat3(const char* varName, const Matrix3& val);
	private:
		uint32_t m_ProgramID;
		void AttachShader(const char* shader, uint32_t shaderType);
		void Link();
	};

}