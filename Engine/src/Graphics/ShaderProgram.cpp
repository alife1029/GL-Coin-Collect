#include "Engine/Graphics/ShaderProgram.h"
#include "Engine/File.h"
#include <glad/glad.h>

namespace engine {

	ShaderProgram::ShaderProgram(const char* vs, const char* fs)
	{
		m_ProgramID = glCreateProgram();
		AttachShader(vs, GL_VERTEX_SHADER);
		AttachShader(fs, GL_FRAGMENT_SHADER);
		Link();
	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ProgramID);
	}

	void ShaderProgram::Use()
	{
		glUseProgram(m_ProgramID);
	}

	void ShaderProgram::AttachShader(const char* shader, uint32_t shaderType)
	{
		// Read shader source file
		std::string shaderSource = File::ReadFile(shader);
		const char* chShaderSource = shaderSource.c_str();

		// Create shader
		uint32_t shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &chShaderSource, nullptr);
		glCompileShader(shaderID);

#ifdef _DEBUG
		// Shader compile error handling
		int isCompiled;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		// If compile status unsuccessfull
		if (!isCompiled)
		{
			switch (shaderType)
			{
			case GL_VERTEX_SHADER:
				printf("Failed to compile Vertex Shader!\n"); break;
			case GL_FRAGMENT_SHADER:
				printf("Failed to compile Fragment Shader!\n"); break;
			default:
				printf("Failed to compile Shader!\n"); break;
			}
			printf("File: %s\n", shader);

			char* log;
			int logLength;

			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
			log = (char*)malloc(logLength);

			printf("\nGPU Log:\n%s\n\n\n", log);

			free(log);
		}
#endif

		glAttachShader(m_ProgramID, shaderID);
	}

	void ShaderProgram::Link()
	{
		glLinkProgram(m_ProgramID);

#ifdef _DEBUG
		// Shader compile error handling
		int isLinked;
		glGetProgramiv(m_ProgramID, GL_COMPILE_STATUS, &isLinked);
		// If compile status unsuccessfull
		if (!isLinked)
		{
			char* log;
			int logLength;

			glGetShaderiv(m_ProgramID, GL_INFO_LOG_LENGTH, &logLength);
			log = (char*)malloc(logLength);

			printf("Program Linking Error!\nGPU Log:\n%s\n\n\n", log);

			free(log);
		}
#endif
	}

	uint32_t ShaderProgram::GetRendererID() { return m_ProgramID; }

	void ShaderProgram::SetUniformVec2(const char* varName, const Vector2& val)
	{
		glUniform2f(glGetUniformLocation(m_ProgramID, varName), val.x, val.y);
	}

	void ShaderProgram::SetUniformVec4(const char* varName, const Vector4& val)
	{
		glUniform4f(glGetUniformLocation(m_ProgramID, varName), val.r, val.g, val.b, val.a);
	}

	void ShaderProgram::SetUniformMat3(const char* varName, const Matrix3& val)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, varName), 1, GL_FALSE, (GLfloat*)&val);
	}

}