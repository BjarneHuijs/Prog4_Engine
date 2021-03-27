#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

Idiot_Engine::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font, const Color& color)
	: m_NeedsUpdate( true )
	, m_Text( text )
	, m_Font( font )
	, m_Color( color )
	, m_Texture( nullptr )
{ }

void Idiot_Engine::TextObject::FixedUpdate(const float deltaTime){ deltaTime; }

void Idiot_Engine::TextObject::Update(const float deltaTime)
{
	deltaTime;
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

void Idiot_Engine::TextObject::LateUpdate(const float deltaTime){ deltaTime; }

void Idiot_Engine::TextObject::Render(const float nextFrameTime) const
{
	if (m_Texture != nullptr)
	{
		nextFrameTime;
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void Idiot_Engine::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void Idiot_Engine::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}


