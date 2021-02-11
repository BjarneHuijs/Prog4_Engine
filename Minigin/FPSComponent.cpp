#include "MiniginPCH.h"
#include "FPSComponent.h"

//#include "Renderer.h"

dae::FPSComponent::FPSComponent(const std::string& text, const std::shared_ptr<Font>& font)
	: TextComponent(text, font)
	, m_StartTime(std::chrono::high_resolution_clock::now())
	, m_FPS(0)
	, m_NrOfFrames(0)
{}

void dae::FPSComponent::LateUpdate(const float deltaTime)
{
	deltaTime;
	const auto currentTime{ std::chrono::high_resolution_clock::now() };

	m_FPS = int(m_NrOfFrames / std::chrono::duration<float>(currentTime - m_StartTime).count());
	SetText(m_FPS + "");
	m_NrOfFrames++;
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
