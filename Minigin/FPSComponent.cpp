#include "MiniginPCH.h"
#include "FPSComponent.h"


dae::FPSComponent::FPSComponent(const std::string& name, const std::string& text, const std::shared_ptr<Font>& font, const Color& color)
	: TextComponent(name, text, font, color)

{}

void dae::FPSComponent::FixedUpdate(const float deltaTime)
{
	deltaTime;
}

void dae::FPSComponent::Update(const float deltaTime)
{
	SetText(std::to_string(static_cast<int>(1 / deltaTime)));
	TextComponent::Update(deltaTime);
}

void dae::FPSComponent::LateUpdate(const float deltaTime)
{
	deltaTime;
}


//void dae::FPSComponent::Render(const float nextFrameTime) const
//{
//	if (m_Texture != nullptr)
//	{
//		nextFrameTime;
//		const auto pos = m_Transform.GetPosition();
//		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
//	}
//}
