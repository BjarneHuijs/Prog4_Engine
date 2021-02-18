#include "MiniginPCH.h"
#include "FPSComponent.h"

dae::FPSComponent::FPSComponent(const std::string& text, const std::shared_ptr<Font>& font, const Color& color)
	: TextComponent(text, font, color)
{}

void dae::FPSComponent::FixedUpdate(const float deltaTime)
{
	deltaTime;
}

void dae::FPSComponent::Update(const float deltaTime)
{
	deltaTime;
	SetText(std::to_string(static_cast<int>(1 / deltaTime)));
	TextComponent::Update(deltaTime);
}

void dae::FPSComponent::LateUpdate(const float deltaTime)
{
	deltaTime;

}

