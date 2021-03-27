#include "MiniginPCH.h"
#include "FPSComponent.h"


Idiot_Engine::FPSComponent::FPSComponent(const std::string& name, const std::string& text, const std::shared_ptr<Font>& font, const Color& color)
	: TextComponent(name, text, font, color)

{}

void Idiot_Engine::FPSComponent::FixedUpdate(const float)
{
	//deltaTime;
}

void Idiot_Engine::FPSComponent::Update(const float deltaTime)
{
	SetText(std::to_string(static_cast<int>(1 / deltaTime)));
	TextComponent::Update(deltaTime);
}

void Idiot_Engine::FPSComponent::LateUpdate(const float)
{
	//deltaTime;
}


//void Idiot_Engine::FPSComponent::Render(const float nextFrameTime) const
//{
//	if (m_Texture != nullptr)
//	{
//		nextFrameTime;
//		const auto pos = m_Transform.GetTransform();
//		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
//	}
//}
