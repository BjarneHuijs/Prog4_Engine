#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "GameObject.h"

#include <SDL_rect.h>
#include <SDL_render.h>



#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

using namespace Idiot_Engine;

SpriteComponent::SpriteComponent(const std::string& name, int nrOfFrames)
	: BaseComponent(name)
	, m_Source()
	, m_Destination()
	, m_Scale(1.f, 1.f)
	, m_NrOfFrames(nrOfFrames)
{}

void SpriteComponent::Render(const float) const
{
	//nextFrame
	const auto& pos = m_pParent->GetTransform().GetPosition();
	if (m_Texture)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Source, m_Destination);
	}
}

void SpriteComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);

	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &m_Source.w, &m_Source.h);
	m_Source.w /= m_NrOfFrames;
	m_Destination.w = int(m_Source.w * m_Scale.x);
	m_Destination.h = int(m_Source.h * m_Scale.y);
}

void SpriteComponent::SetScale(float xScale, float yScale)
{
	m_Scale.x = xScale;
	m_Scale.y = yScale;
}

void SpriteComponent::ToNextFrame()
{
	m_Source.x += m_Source.w;
	if(m_Source.x >= m_Source.w * m_NrOfFrames)
	{
		m_Source.x = 0;
	}
}

void SpriteComponent::ToTargetFrame(int frameIndex)
{
	m_Source.x = frameIndex * m_Source.w;
	if (m_Source.x >= m_Source.w * m_NrOfFrames)
	{
		m_Source.x = 0;
	}
}
