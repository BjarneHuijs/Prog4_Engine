#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

using namespace Idiot_Engine;

TextureComponent::TextureComponent(const std::string& name)
	: BaseComponent(name)
{}

void TextureComponent::Render(const float) const
{
	//nextFrame
	if (m_pParent)
	{
		const auto pos = m_pParent->GetTransform().GetPosition();
		if (m_Texture)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		}
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}