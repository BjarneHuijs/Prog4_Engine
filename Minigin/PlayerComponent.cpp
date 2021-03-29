#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"

using namespace Idiot_Engine;
PlayerComponent::PlayerComponent(const std::string& name)
	: BaseComponent(name)
	, m_Health(100)
	, m_NrLives(3)
	, m_Score(0)
	, m_NrOfDiscsRemaining(10)
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
		else
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
		}
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
	if (m_Health >= 1) 
	{
		m_Health = 0;
		m_NrLives--;

		std::shared_ptr<SubjectComponent> subject{ nullptr };
		if (m_pParent)
		{
			subject = m_pParent->GetComponentByType<SubjectComponent>();


			if (subject)
			{
				subject->NotifyObservers(*m_pParent, ObserverEvent{ ("Lives: " + std::to_string(m_NrLives)), EventTypes::LivesChanged });
			}
		}
	}

}

void PlayerComponent::ChangeColor()
{
	m_Score += 25;
	std::shared_ptr<SubjectComponent> subject{ nullptr };
	if (m_pParent)
	{
		subject = m_pParent->GetComponentByType<SubjectComponent>();


		if (subject)
		{
			subject->NotifyObservers(*m_pParent, ObserverEvent{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });
		}
	}
}

void PlayerComponent::KillCoilyWithDisc()
{
	if (m_NrOfDiscsRemaining > 0) 
	{
		m_Score += 500;
		m_NrOfDiscsRemaining--;
	}

	std::shared_ptr<SubjectComponent> subject{ nullptr };
	if (m_pParent)
	{
		subject = m_pParent->GetComponentByType<SubjectComponent>();


		if (subject)
		{
			subject->NotifyObservers(*m_pParent, ObserverEvent{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });
		}
	}
}

void PlayerComponent::RemainingDiscsScore()
{
	m_Score += 50 * m_NrOfDiscsRemaining;
	m_NrOfDiscsRemaining = 0;

	std::shared_ptr<SubjectComponent> subject{ nullptr };
	if (m_pParent)
	{
		subject = m_pParent->GetComponentByType<SubjectComponent>();


		if (subject)
		{
			subject->NotifyObservers(*m_pParent, ObserverEvent{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });
		}
	}
}

void PlayerComponent::CatchNPC()
{
	m_Score += 300;
	std::shared_ptr<SubjectComponent> subject{ nullptr };
	if (m_pParent)
	{
		subject = m_pParent->GetComponentByType<SubjectComponent>();


		if (subject)
		{
			subject->NotifyObservers(*m_pParent, ObserverEvent{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });
		}
	}
}


