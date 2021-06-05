#include "QBertGamePCH.h"
#include "QBertComponent.h"

#include "../Level/Level_1/Level_1.h"
#include "GameObject.h"
#include "Structs.h"
#include "SubjectComponent.h"
#include "../Level/Tile/TileComponent.h"

using namespace Idiot_Engine;
QBertComponent::QBertComponent(const std::string& name, Level_1* pLevel, float movementSpeed)
	: PlayerComponent(name)
	, m_NrLives(3)
	, m_Score(0)
	, m_NrOfDiscsRemaining(10)
	, m_CurrentTile(0)
	, m_pLevel(pLevel)
	, m_MovementSpeed(movementSpeed)
	, m_TargetPos()
	, m_PosOffset()
	, m_bMoving(false)
{
	m_TargetPos = m_pLevel->GetTiles()[m_CurrentTile].Position.GetPosition2D();
}

void QBertComponent::FixedUpdate(const float)
{}

void QBertComponent::Update(const float deltaTime)
{
	std::shared_ptr<SubjectComponent> subject{ nullptr };
	const Transform transform{ m_pParent->GetTransform() };
	if (m_pParent)
	{
		if (m_bMoving) 
		{
			const glm::vec2 movement = (transform.GetPosition2D() + (m_TargetPos - transform.GetPosition2D()) * deltaTime * m_MovementSpeed);

			if (glm::length(m_TargetPos - movement) < 3.0f)
			{
				m_pParent->SetPosition(m_TargetPos.x, m_TargetPos.y);
				m_bMoving = false;
			}else
			{
				m_pParent->SetPosition(movement.x, movement.y);
			}
		}
		
		subject = m_pParent->GetComponentByType<SubjectComponent>();


		//deltaTime;
		if (m_Health < 1 || m_CurrentTile == -1)
		{
			//std::cout << "player died" << std::endl;
			m_Health += deltaTime;


			if (subject)
			{
				subject->NotifyObservers(*m_pParent, ObserverEvent{ "PlayerDied", EventTypes::LivesChanged });
			}
			
			m_CurrentTile = 0;
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

void QBertComponent::LateUpdate(const float)
{
}

void QBertComponent::Render(const float) const
{
}

void QBertComponent::Kill()
{
	if (m_Health >= m_MaxHealth)
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

void QBertComponent::ChangeColor()
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

void QBertComponent::KillCoilyWithDisc()
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

void QBertComponent::RemainingDiscsScore()
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

void QBertComponent::CatchNPC()
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

void QBertComponent::MoveTopLeft()
{
	auto tiles = m_pLevel->GetTiles();
	const int targetIndex{ tiles[m_CurrentTile].TopLeft };
	if (targetIndex != -1 && !m_bMoving) 
	{
		m_TargetPos = tiles[targetIndex].Position.GetPosition2D();
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_CurrentTile = targetIndex;
		m_bMoving = true;
	}
}

void QBertComponent::MoveTopRight()
{
	auto tiles = m_pLevel->GetTiles();
	const int targetIndex{ tiles[m_CurrentTile].TopRight };
	if (targetIndex != -1 && !m_bMoving)
	{
		m_TargetPos = tiles[targetIndex].Position.GetPosition2D();
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_CurrentTile = targetIndex;
		m_bMoving = true;
	}
}

void QBertComponent::MoveBotLeft()
{
	auto tiles = m_pLevel->GetTiles();
	const int targetIndex{ tiles[m_CurrentTile].BotLeft };
	if (targetIndex != -1 && !m_bMoving)
	{
		m_TargetPos = tiles[targetIndex].Position.GetPosition2D();
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_CurrentTile = targetIndex;
		m_bMoving = true;
	}
}

void QBertComponent::MoveBotRight()
{
	auto tiles = m_pLevel->GetTiles();
	const int targetIndex{ tiles[m_CurrentTile].BotRight };
	if (targetIndex != -1 && !m_bMoving)
	{
		m_TargetPos = tiles[targetIndex].Position.GetPosition2D();
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_CurrentTile = targetIndex;
		m_bMoving = true;
	}
}

void QBertComponent::SetPosOffset(float offset)
{
	m_PosOffset = offset;
}
