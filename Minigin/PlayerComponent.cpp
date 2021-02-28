#include "MiniginPCH.h"
#include "PlayerComponent.h"

dae::PlayerComponent::PlayerComponent()
	: m_Health{ 100 }
{}

void dae::PlayerComponent::FixedUpdate(const float deltaTime)
{
	deltaTime;
}

void dae::PlayerComponent::Update(const float deltaTime)
{
	deltaTime;
	if (m_Health <= 0)
	{
		std::cout << "player died" << std::endl;
	}
}

void dae::PlayerComponent::LateUpdate(const float deltaTime)
{
	deltaTime;
}

void dae::PlayerComponent::Render(const float nextFrame) const
{
	nextFrame;
}

void dae::PlayerComponent::Kill()
{
	m_Health = 0;
}
