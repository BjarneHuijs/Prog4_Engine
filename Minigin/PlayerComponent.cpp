#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"

using namespace Idiot_Engine;
PlayerComponent::PlayerComponent(const std::string& name, int health, int maxHealth)
	: BaseComponent(name)
	, m_Health(static_cast<float>(health))
	, m_MaxHealth(static_cast<float>(maxHealth))
{}

void PlayerComponent::FixedUpdate(const float)
{
	//deltaTime;
}

void PlayerComponent::Update(const float deltaTime)
{
	std::shared_ptr<SubjectComponent> subject{nullptr};
	if (m_pParent)
	{
		subject = m_pParent->GetComponentByType<SubjectComponent>();
	

		//deltaTime;
		if (m_Health < 1)
		{
			//std::cout << "player died" << std::endl;
			m_Health += deltaTime;


			if (subject)
			{
				subject->NotifyObservers(*m_pParent, ObserverEvent{ "PlayerDied", EventTypes::LivesChanged });
			}
		}
		/*else
		{
			m_Health = 1;

			if (m_NrLives <= 0)
			{
				if (subject)
				{
					subject->NotifyObservers(*m_pParent, ObserverEvent{ "Game Over", EventTypes::PlayerDeath });
				}
			}
			else
			{
				if (subject)
				{
					subject->NotifyObservers(*m_pParent, ObserverEvent{ ("Lives: " + std::to_string(m_NrLives)), EventTypes::LivesChanged });
				}
			}
		}*/
	}
}

void PlayerComponent::LateUpdate(const float)
{
	//deltaTime;

}

void PlayerComponent::Render(const float) const
{
	//nextFrame;
}

void PlayerComponent::Kill()
{
	if (m_Health >= m_MaxHealth) 
	{
		m_Health = 0;
		//m_NrLives--;

		std::shared_ptr<SubjectComponent> subject{ nullptr };
		if (m_pParent)
		{
			subject = m_pParent->GetComponentByType<SubjectComponent>();


			if (subject)
			{
				subject->NotifyObservers(*m_pParent, ObserverEvent{ ("Player died"), EventTypes::LivesChanged });
			}
		}
	}

}
