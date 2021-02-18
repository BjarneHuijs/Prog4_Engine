#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "Structs.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public SceneObject
	{
	public:
		void FixedUpdate(const float deltaTime) override;
		void Update(const float deltaTime) override;
		void LateUpdate(const float deltaTime) override;
		void Render(const float nextFrameTime) const override;

		void SetText(const std::string& text);
		void SetPosition(const float x, const float y);

		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font, const Color& color = { 255, 255,255 });
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		Color m_Color;
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
