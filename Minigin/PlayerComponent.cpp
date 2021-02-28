#include "MiniginPCH.h"
#include "PlayerComponent.h"

dae::PlayerComponent::PlayerComponent()
	: m_Health(100)
	, m_NrLives(3)
	, m_Score(0)
	, m_NrOfDiscsRemaining(10)
{}

void dae::PlayerComponent::FixedUpdate(const float deltaTime)
{
	deltaTime;
}

void dae::PlayerComponent::Update(const float deltaTime)
{
	
	deltaTime;
	if (m_Health < 1)
	{
		//std::cout << "player died" << std::endl;
		m_Health += deltaTime;
		NotifyObservers(*m_pParent, Event{ "PlayerDied", EventTypes::LivesChanged });

	}
	else{
		m_Health = 1;

		if (m_NrLives <= 0)
		{
			NotifyObservers(*m_pParent, Event{ "Game Over", EventTypes::PlayerDeath });
		}
		else
		{
			NotifyObservers(*m_pParent, Event{ ("Lives: " + std::to_string(m_NrLives)), EventTypes::LivesChanged });

		}
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
	if (m_Health >= 1) 
	{
		m_Health = 0;
		m_NrLives--;
		//NotifyObservers(*m_pParent, Event{ ("Lives: " + std::to_string(m_NrLives)), EventTypes::LivesChanged });
	}

}

void dae::PlayerComponent::ChangeColor()
{
	m_Score += 25;
	NotifyObservers(*m_pParent, Event{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });

}

void dae::PlayerComponent::KillCoilyWithDisc()
{
	if (m_NrOfDiscsRemaining > 0) 
	{
		m_Score += 500;
		m_NrOfDiscsRemaining--;
	}
	NotifyObservers(*m_pParent, Event{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });

}

void dae::PlayerComponent::RemainingDiscsScore()
{
	m_Score += 50 * m_NrOfDiscsRemaining;
	m_NrOfDiscsRemaining = 0;
	NotifyObservers(*m_pParent, Event{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });

}

void dae::PlayerComponent::CatchNPC()
{
	m_Score += 300;
	NotifyObservers(*m_pParent, Event{ "Score: " + std::to_string(m_Score), EventTypes::ScoreChanged });

}


