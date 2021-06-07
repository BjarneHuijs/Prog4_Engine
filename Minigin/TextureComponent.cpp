#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextureComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

using namespace Idiot_Engine;

TextureComponent::TextureComponent(const std::string& name)
	: BaseComponent(name)
	, m_Source()
	, m_Destination()
	, m_Scale(1.f, 1.f)
{

}

void TextureComponent::Render(const float) const
{
	//nextFrame
	//const auto& pos = m_pParent->GetTransform().GetPosition();
	if (m_Texture)
	{
		const glm::vec2 parentPos{ m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y };
		const glm::vec2 pos{ parentPos + m_RelativePosition };
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Source, m_Destination);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &m_Source.w, &m_Source.h);
	m_Destination.w = static_cast<int>(m_Source.w * m_Scale.x);
	m_Destination.h = static_cast<int>(m_Source.h * m_Scale.y);
}

void TextureComponent::SetScale(float xScale, float yScale)
{
	m_Scale.x = xScale;
	m_Scale.y = yScale;
}

void TextureComponent::SetRelativePosition(const float x, const float y)
{
	m_RelativePosition = { x, y };
}
