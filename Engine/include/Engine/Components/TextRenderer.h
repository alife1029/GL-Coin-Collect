#pragma once

#include "Engine/API.h"
#include "Engine/Entity/Component.h"
#include "Engine/Math/Vector4.h"
#include "Transform.h"

namespace engine {

	class ShaderProgram;
	struct FontFamily;

	enum class Anchor
	{
		LEFT,
		CENTER,
		RIGHT,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};

	/*
	enum class TextAlign
	{
		LEFT,
		CENTER,
		RIGHT
	};
	*/

	class ENGINE_API TextRenderer : public Component
	{
	public:
		void Update() override;
		std::string GetType() override;

		// Setters
		void SetFont(const char* font);
		void SetText(const char* text);
		void SetAnchor(Anchor anchor);
		//void SetAlign(TextAlign align);
		void SetColor(const Vector4& color);
		void SetColor(float r, float g, float b, float a);

		// Getters
		std::string GetText();
		Anchor GetAnchor();
		//TextAlign GetTextAlign();
		Vector4 GetColor();
	private:
		void OnAttach() override;
	private:
		Anchor m_Anchor = Anchor::LEFT;
		//TextAlign m_Align = TextAlign::LEFT;
		std::string m_Text;
		FontFamily* m_Font = nullptr;
		ShaderProgram* m_Shader = nullptr;
		Vector4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		uint32_t m_VAO = 0;
		uint32_t m_VBO = 0;
		uint32_t m_IBO = 0;
		Transform* m_Transform;
	};

}