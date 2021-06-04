#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextureComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>



#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

using namespace Idiot_Engine;

TextureComponent::TextureComponent(const std::string& name, int nrOfFrames)
	: BaseComponent(name)
	, m_Source()
	, m_Destination()
	, m_NrOfFrames(nrOfFrames)
{

}

void TextureComponent::Render(const float) const
{
	//nextFrame
	const auto& pos = m_pParent->GetTransform().GetPosition();
	if (m_Texture)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Source, m_Destination);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &m_Source.w, &m_Source.h);
	m_Source.w /= m_NrOfFrames;
	m_Destination.w = m_Source.w;
	m_Destination.h = m_Source.h;
}