#include "QBertGamePCH.h"
#include "QBertComponent.h"

#include "../Level/Level_1/Level_1.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Structs.h"
#include "SubjectComponent.h"
#include "../Level/Tile/TileComponent.h"

using namespace Idiot_Engine;
QBertComponent::QBertComponent(const std::string& name, int level, float movementSpeed)
	: PlayerComponent(name)
	, m_NrLives(3)
	, m_Score(0)
	, m_NrOfDiscsRemaining(10)
	, m_CurrentTile(0)
	, m_CurrentLevel(level)
	, m_TargetPos()
	, m_CurrentMovementSpeed(movementSpeed)
	, m_MovementSpeed(movementSpeed)
	, m_LiftMovementSpeed(movementSpeed / 2)
	, m_PosOffset()
	, m_bMoving(false)
	, m_bOnDisc(false)
	, m_DiscTarget(INT16_MIN)
	, m_DiscId(INT16_MIN)
{}

void QBertComponent::FixedUpdate(const float)
{}

void QBertComponent::Update(const float deltaTime)
{
	std::shared_ptr<SubjectComponent> subject{ nullptr };
	const Transform transform{ m_pParent->GetTransform() };
	if (m_pParent)
	{
		if(TileManager::GetInstance().LevelCleared(m_CurrentLevel - 1))
		{
			ServiceLocator::GetAudio()->QueueSound(6); // id 6 = win
			if (m_CurrentLevel < 3)
			{
				ResetLevel(m_CurrentLevel);
				RemainingDiscsScore();
				m_CurrentLevel++;
				m_CurrentTile = 0;
				m_NrLives = 3;
				m_Health = 0;
				ResetToLevelStart();
				SetCurrentLevel(m_CurrentLevel);
				SceneManager::GetInstance().SetActiveScene("Level_" + std::to_string(m_CurrentLevel));
			}
			else
			{
				std::cout << "Lvl 3 cleared -> Game Over!!!!!" << std::endl;
				m_Score = 0;
				m_CurrentLevel = 1;
				ResetLevels();
				SetCurrentLevel(m_CurrentLevel);
				SceneManager::GetInstance().SetActiveScene("Level_1");
			}
		}

		subject = m_pParent->GetComponentByType<SubjectComponent>();
		if (m_bMoving) 
		{
			const glm::vec2 movement = (transform.GetPosition2D() + (m_TargetPos - transform.GetPosition2D()) * deltaTime * m_CurrentMovementSpeed);

			if (glm::length(m_TargetPos - movement) < 3.0f)
			{
				m_CurrentMovementSpeed = m_MovementSpeed;
				
				m_pParent->SetPosition(m_TargetPos.x, m_TargetPos.y);
				m_bMoving = false;
				
				if (subject && m_Health == m_MaxHealth)
				{
					subject->NotifyObservers(*m_pParent, ObserverEvent{ "TileChanged", EventTypes::TileChanged });
				}

				if (m_bOnDisc) 
				{
					DiscTaken();
				}
			}
			else
			{
				m_pParent->SetPosition(movement.x, movement.y);
			}
		}

		//deltaTime;
		if (m_Health < m_MaxHealth || m_CurrentTile == -1)
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
			m_Health = m_MaxHealth;

			if (m_NrLives <= 0)
			{
				if (subject)
				{
					subject->NotifyObservers(*m_pParent, ObserverEvent{ "Game Over", EventTypes::PlayerDeath });
				}
				if (subject)
				{
					subject->NotifyObservers(*m_pParent, ObserverEvent{ " ", EventTypes::PlayerDeath });
				}
				ServiceLocator::GetAudio()->QueueSound(7); // id 7 = game over
				SceneManager::GetInstance().SetActiveScene("Level_1");
				m_Score = 0;
				m_CurrentLevel = 1;
				ResetLevels();
				SetCurrentLevel(m_CurrentLevel);
				
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
	ServiceLocator::GetAudio()->QueueSound(4); // id 4 = fall
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

void QBertComponent::ChangeColor(int index)
{
	if (index == m_CurrentTile)
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
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->TopLeft };
	//if (targetIndex != -1 && !m_bMoving) 
	if (!m_bMoving && m_Health == m_MaxHealth)
	{
		if(targetIndex == -1 && !CheckForDisc(m_CurrentLevel))
		{
			Kill();
			m_TargetPos = tiles[0]->Position.GetPosition2D();
			m_CurrentTile = 0;
		}
		else if (targetIndex != -1)
		{
			ServiceLocator::GetAudio()->QueueSound(1); // id 1 = move
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
		}
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_bMoving = true;
	}
}

void QBertComponent::MoveTopRight()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->TopRight };
	if (!m_bMoving && m_Health == m_MaxHealth)
	{
		if (targetIndex == -1 && !CheckForDisc(m_CurrentLevel))
		{
			Kill();
			m_TargetPos = tiles[0]->Position.GetPosition2D();
			m_CurrentTile = 0;
		}
		else if(targetIndex != -1)
		{
			ServiceLocator::GetAudio()->QueueSound(1); // id 1 = move
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
		}
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_bMoving = true;
	}
}

void QBertComponent::MoveBotLeft()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotLeft };
	if (!m_bMoving && m_Health == m_MaxHealth)
	{
		if (targetIndex == -1 && !CheckForDisc(m_CurrentLevel))
		{
			Kill();
			m_TargetPos = tiles[0]->Position.GetPosition2D();
			m_CurrentTile = 0;
		}
		else if (targetIndex != -1)
		{
			ServiceLocator::GetAudio()->QueueSound(1); // id 1 = move
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
		}
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_bMoving = true;
	}
}

void QBertComponent::MoveBotRight()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotRight };
	if (!m_bMoving && m_Health == m_MaxHealth)
	{
		if (targetIndex == -1 && !CheckForDisc(m_CurrentLevel))
		{
			Kill();
			m_TargetPos = tiles[0]->Position.GetPosition2D();
			m_CurrentTile = 0;
		}
		else if (targetIndex != -1)
		{
			ServiceLocator::GetAudio()->QueueSound(1); // id 1 = move
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
		}
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;
		m_bMoving = true;
	}
}

void QBertComponent::SetPosOffset(float offset)
{
	m_PosOffset = offset;
}

int QBertComponent::GetCurrentTileID() const
{
	return m_CurrentTile;
}

int QBertComponent::GetCurrentLevelNr() const
{
	return m_CurrentLevel;
}

void QBertComponent::ResetToLevelStart()
{
	m_TargetPos = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1)[m_CurrentTile]->Position.GetPosition2D();
	m_TargetPos.x += m_PosOffset;
	m_TargetPos.y -= m_PosOffset;
	m_pParent->SetPosition(m_TargetPos.x, m_TargetPos.y);
}

void QBertComponent::DiscTaken()
{
	ServiceLocator::GetAudio()->QueueSound(5); // id 5 = lift
	m_TargetPos = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1)[m_DiscTarget]->Position.GetPosition2D();
	m_TargetPos.x += m_PosOffset;
	m_TargetPos.y -= m_PosOffset;

	std::shared_ptr<SubjectComponent> subject{ nullptr };

	subject = m_pParent->GetComponentByType<SubjectComponent>();
	if (subject && m_Health == m_MaxHealth)
	{
		subject->NotifyObservers(*m_pParent, ObserverEvent{ "Disc Changed", EventTypes::DiscChanged });
	}

	m_DiscTarget = INT16_MIN;
	m_DiscId = INT16_MIN;

	m_bOnDisc = false;
	m_bMoving = true;
	
	m_CurrentTile = 0;
	m_CurrentMovementSpeed = m_LiftMovementSpeed;
	
	m_NrOfDiscsRemaining--;

}

bool QBertComponent::IsOnDisc() const
{
	return m_bOnDisc;
}

int QBertComponent::GetDiscId() const
{
	return m_DiscId;
}

int QBertComponent::GetNrOfLives() const
{
	return m_NrLives;
}

void QBertComponent::SetCurrentLevel(const int level)
{
	m_CurrentLevel = level;
	m_NrOfDiscsRemaining = static_cast<int>(TileManager::GetInstance().GetDiscs(level - 1).size());
}

void QBertComponent::ResetLevels()
{
	ResetLevel(1);
	ResetLevel(2);
	ResetLevel(3);
	m_NrLives = 3;
}

void QBertComponent::ResetLevel(const int level)
{
	std::shared_ptr<SubjectComponent> subject{ nullptr };
	if (m_pParent) 
	{
		m_CurrentTile = 0;
		m_bMoving = false;
		
		m_TargetPos = TileManager::GetInstance().GetTiles(level - 1)[m_CurrentTile]->Position.GetPosition2D();
		m_TargetPos.x += m_PosOffset;
		m_TargetPos.y -= m_PosOffset;

		m_pParent->SetPosition(m_TargetPos.x, m_TargetPos.y);
		
		m_Health = m_MaxHealth;
		subject = m_pParent->GetComponentByType<SubjectComponent>();

		TileManager::GetInstance().ClearTiles(m_CurrentLevel - 1);
		
		if (subject && m_Health == m_MaxHealth)
		{
			subject->NotifyObservers(*m_pParent, ObserverEvent{ "TileChanged", EventTypes::TileChanged });
		}
		if (subject && m_Health == m_MaxHealth)
		{
			subject->NotifyObservers(*m_pParent, ObserverEvent{ "DiscChanged", EventTypes::DiscChanged });
		}
		
		m_Health = 0;
		m_DiscTarget = INT16_MIN;
		m_DiscId = INT16_MIN;

	}
}

bool QBertComponent::CheckForDisc(const int)
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	auto discs = TileManager::GetInstance().GetDiscs(m_CurrentLevel - 1);

	for(DiscData* disc : discs)
	{
		if(m_CurrentTile == disc->ConnectedTile && !disc->Used)
		{
			m_TargetPos = disc->Position.GetPosition2D();
			m_DiscTarget = disc->TargetTile;
			m_bOnDisc = true;
			m_DiscId = disc->DiscID;
			return true;
		}
	}

	return false;
}
