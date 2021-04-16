#include "Engine/Components/TextRenderer.h"
#include "Engine/Graphics/ShaderProgram.h"
#include "Engine/Graphics/FontManager.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Entity/GameObject.h"
#include <typeinfo>
#include <glad/glad.h>

namespace engine {

	struct TextVertex
	{
		Vector2 Pos;
		Vector2 TexCoords;
	};

	void TextRenderer::OnAttach()
	{
		m_Transform = GetGameObject()->GetComponent<Transform>();
		if (m_Transform == nullptr)
			throw "You must add Transform before than Text Renderer!";

		// Load Shader
		m_Shader = new ShaderProgram("GLshaders/text.vert", "GLshaders/text.frag");

		// VAO and VBO
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TextVertex) * 4, nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, Pos));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, TexCoords));
		
		// IBO
		uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Disable buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void TextRenderer::Update()
	{
		// Calculate Transform Matrix
		//Matrix3 mtxTransform = Matrix3::Translate(m_Transform->GetPosition()) * Matrix3::Rotate(0.0f) * Matrix3::Scale(m_Transform->GetScale());
		Matrix3 mtxTransform = Matrix3::Identity();

		// Set uniforms
		m_Shader->Use();
		m_Shader->SetUniformVec4("u_TextColor", m_Color);
		m_Shader->SetUniformMat3("u_Transform", mtxTransform);

		// Bind Buffers
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

		float x = m_Transform->GetPosition().x;
		float y = m_Transform->GetPosition().y;
		// Iterate trought all characters
		std::string::const_iterator c;
		for (c = m_Text.begin(); c != m_Text.end(); c++)
		{
			Character ch = m_Font->Characters[*c];
			
			float xPos = x + ch.Bearing.x * m_Transform->GetScale().x;
			float yPos = y - (ch.Size.y - ch.Bearing.y) * m_Transform->GetScale().y;
			float w = ch.Size.x * m_Transform->GetScale().x;
			float h = ch.Size.y * m_Transform->GetScale().y;

			// Update VBO for each character
			float vertices[4][4] = {
				{ xPos,		yPos + h,	0.0f, 0.0f },
				{ xPos,		yPos,		0.0f, 1.0f },
				{ xPos + w,	yPos,		1.0f, 1.0f },
				{ xPos + w,	yPos + h,	1.0f, 0.0f }
			};
			
			// Render glyph over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Render Quad
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			x += (ch.Advance >> 6) * m_Transform->GetScale().x;
		}

		// Unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextRenderer::SetFont(const char* font)
	{
		m_Font = FontManager::LoadFont(font);
	}
	void TextRenderer::SetText(const char* text)
	{
		m_Text = text;
	}
	void TextRenderer::SetColor(const Vector4& color)
	{
		m_Color = color;
	}
	void TextRenderer::SetColor(float r, float g, float b, float a)
	{
		m_Color = { r, g, b, a };
	}

	std::string TextRenderer::GetText() 
	{ 
		return m_Text;
	}
	Vector4 TextRenderer::GetColor()
	{
		return m_Color;
	}

	std::string TextRenderer::GetType() 
	{ 
		return typeid(*this).name(); 
	}

}