#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "PlayerComponent.h"

using namespace Idiot_Engine;

TextComponent::TextComponent(const std::string& name, const std::string& text, const std::shared_ptr<Font>& font, const Color& color)
	: BaseComponent(name)
	, m_NeedsUpdate( true )
	, m_Text( text )
	, m_Font( font )
	, m_Color( color )
	, m_Texture(nullptr)
{}

void TextComponent::FixedUpdate(const float)
{
	//deltaTime;
}

void TextComponent::Update(const float)
{
	//deltaTime;
	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const SDL_Color color = { m_Color.r ,m_Color.g ,m_Color.b };
		
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::LateUpdate(const float)
{
	//deltaTime;
	
}

void TextComponent::Render(const float) const
{
	if (m_Texture != nullptr && m_pParent)
	{
		//nextFrameTime;
		//const auto pos = m_Transform.GetTransform();
		const glm::vec2 parentPos{ m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y };
		const glm::vec2 pos{ parentPos + m_RelativePosition };
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

//void TextComponent::onNotify(const GameObject&, ObserverEvent event)
//{
//	//object;
//	if (event.type == m_Type)
//	{
//		SetText(event.message);
//	}
//}

//void TextComponent::SetParent(GameObject* pParent)
//{
//	if(pParent)
//	{
//		m_pParent = pParent;
//	}
//}

void TextComponent::SetRelativePosition(const float x, const float y)
{
	m_RelativePosition = { x, y };
}
