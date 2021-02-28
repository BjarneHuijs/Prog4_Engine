#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "Structs.h"
#include "Observer.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent, public Observer
	{
	public:
		virtual void FixedUpdate(const float deltaTime) override;
		virtual void Update(const float deltaTime) override;
		virtual void LateUpdate(const float deltaTime) override;
		virtual void Render(const float nextFrameTime) const override;

		void SetText(const std::string& text);
		void SetPosition(const float x, const float y);

		void onNotify(const GameObject& object, Event event) override;
		
		//void SetParent(GameObject* parent) override;

		explicit TextComponent(const std::string& name, const std::string& text, const std::shared_ptr<Font>& font, const Color& color = {255, 255, 255 }, EventTypes type = { EventTypes::All });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent & other) = delete;
		TextComponent(TextComponent && other) = delete;
		TextComponent& operator=(const TextComponent & other) = delete;
		TextComponent& operator=(TextComponent && other) = delete;
	protected:
		bool m_NeedsUpdate{};
		std::string m_Name{};
		std::string m_Text{};
		std::shared_ptr<Font> m_Font{};
		Color m_Color{};
		Transform m_Transform{};
		std::shared_ptr<Texture2D> m_Texture{};
	};
}