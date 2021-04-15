#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Graphics/TextureManager.h"
#include "Engine/Graphics/ShaderProgram.h"
#include "Engine/Entity/GameObject.h"
#include "Engine/Components/Transform.h"
#include <glad/glad.h>
#include <typeinfo>

namespace engine {

	SpriteRenderer::SpriteRenderer()
	{
		m_Shader = new ShaderProgram("GLshaders/sprite.vert", "GLshaders/sprite.frag");
		m_TexID = 0;
		m_VAO = 0;
		m_VBO = 0;
		m_IBO = 0;
	}
	SpriteRenderer::SpriteRenderer(const char* imageName)
	{
		m_Shader = new ShaderProgram("GLshaders/sprite.vert", "GLshaders/sprite.frag");
		SetImage(imageName);
		m_VAO = 0;
		m_VBO = 0;
		m_IBO = 0;
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete m_Shader;

		if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
		if (m_VBO) glDeleteBuffers(1, &m_VBO);
		if (m_IBO) glDeleteBuffers(1, &m_IBO);
	}

	// Generates VBO, VAO, IBO and Shader Program
	void SpriteRenderer::OnAttach()
	{
		if (GetGameObject()->GetComponent<Transform>() == nullptr)
			throw "You must attach Transform before than Sprite Renderer!";

		m_Shader->Use();

		// Get size from Transform component of the Game Object
		Vector2 size = GetGameObject()->GetComponent<Transform>()->GetSize();

		// Vertices and indices
		struct Vertex
		{
			Vector2 Position;
			Vector2 TexCoords;
		};
		Vertex vertices[4] = {
			{ {-size.x / 2.0f, -size.y / 2.0f }, { 0.0f, 0.0f } },
			{ { size.x / 2.0f, -size.y / 2.0f }, { 1.0f, 0.0f } },
			{ { size.x / 2.0f,  size.y / 2.0f }, { 1.0f, 1.0f } },
			{ {-size.x / 2.0f,  size.y / 2.0f }, { 0.0f, 1.0f } }
		};
		uint32_t indices[6] = { 0, 1, 2, 0, 2, 3 };

		// Generate VBO, VAO and IBO
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// Generates Texture
	void SpriteRenderer::SetImage(const char* imageName)
	{
		m_TexID = TextureManager::LoadTexture(imageName);
	}

	// Render texture
	void SpriteRenderer::Update()
	{
		m_Shader->Use();
		Transform* t = GetGameObject()->GetComponent<Transform>();
		Matrix3 transform = Matrix3::Translate(t->GetPosition()) * Matrix3::Rotate(0.0f) * Matrix3::Scale(t->GetScale());
		m_Shader->SetUniformMat3("u_Transform", transform);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	std::string SpriteRenderer::GetType() { return typeid(*this).name(); }

}