#include "QBertGamePCH.h"
#include "SlimeComponent.h"

#include "../../Level/Levels/GameLevels.h"
#include "GameObject.h"
#include "SubjectComponent.h"
#include "../../Level/Tile/TileManager.h"

using namespace Idiot_Engine;
SlimeComponent::SlimeComponent(const std::string& name, bool isRedSlime, int id, int spawnTile, int level, float movementSpeed)
	: NPCBaseComponent(name, id, spawnTile, level, movementSpeed)
	, m_bRed(isRedSlime)

{
	m_TargetPos = TileManager::GetInstance().GetTile(level - 1, spawnTile)->Position.GetPosition2D();
}

void SlimeComponent::FixedUpdate(const float)
{}

void SlimeComponent::Update(const float deltaTime)
{
	if(m_bPaused)
	{
		m_PauseTimer += deltaTime;
		if(m_PauseTimer >= m_PauseTime)
		{
			m_bPaused = false;
			m_PauseTimer = 0.f;
		}
	}
	else 
	{
		std::shared_ptr<SubjectComponent> subject{ nullptr };
		const Transform transform{ m_pParent->GetTransform() };
		if (m_pParent)
		{
			subject = m_pParent->GetComponentByType<SubjectComponent>();
			if (m_bFalling)
			{
				m_TargetPos.y += (m_PosOffset / 4);

				if (m_TargetPos.y > 400)
				{
					m_bDead = true;
					std::cout << "fallen off map" << std::endl;
				}
				else 
				{

					const glm::vec2 movement = (transform.GetPosition2D() + (m_TargetPos - transform.GetPosition2D()) * deltaTime * m_MovementSpeed);
					m_pParent->SetPosition(movement.x, movement.y);
				}
			}
			else if (m_bMoving)
			{
				const glm::vec2 movement = (transform.GetPosition2D() + (m_TargetPos - transform.GetPosition2D()) * deltaTime * m_MovementSpeed);


				if (glm::length(m_TargetPos - movement) < 3.0f)
				{
					m_pParent->SetPosition(m_TargetPos.x, m_TargetPos.y);
					m_bMoving = false;
					
					//if (subject)// && m_Health == m_MaxHealth)
					//{
					//	subject->NotifyObservers(*m_pParent, ObserverEvent{ "SlimeMoved", EventTypes::SlimeMoved });
					//}
				}
				else
				{
					m_pParent->SetPosition(movement.x, movement.y);
				}

			}
			else
			{
				const int nextMove = rand() % 2;
				if (nextMove == 0)
				{
					MoveBotLeft();
				}
				else
				{
					MoveBotRight();
				}
			}

			//deltaTime;
			/*if (m_Health < m_MaxHealth || m_CurrentTile == -1)
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
			}*/
		}
	}
}

void SlimeComponent::LateUpdate(const float)
{}

void SlimeComponent::Render(const float) const
{
}

void SlimeComponent::Kill()
{
	ServiceLocator::GetAudio()->QueueSound(4); // id 4 = fall
	/*if (m_Health >= m_MaxHealth)
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
	}*/
}

void SlimeComponent::Fall()
{
	std::shared_ptr<SubjectComponent> subject{ nullptr };
	if (m_pParent)
	{
		subject = m_pParent->GetComponentByType<SubjectComponent>();
		m_bFalling = true;
		if (subject)
		{
			//subject->NotifyObservers(*m_pParent, ObserverEvent{ ("Lives: " + std::to_string(m_NrLives)), EventTypes::LivesChanged });
		}
	}
}

void SlimeComponent::MoveTopLeft(){}
void SlimeComponent::MoveTopRight(){}

void SlimeComponent::MoveBotLeft()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotLeft };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
		tile->npcOnTile = false;
		if (targetIndex == -1)
		{
			Fall();
		}
		else
		{
			
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset / 4);

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcOnTile = true;
		}
		m_bMoving = true;
	}
}

void SlimeComponent::MoveBotRight()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotRight };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
		tile->npcOnTile = false;
		if (targetIndex == -1)
		{
			Fall();
		}
		else
		{

			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset / 4);
			
			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcOnTile = true;
		}
		m_bMoving = true;
	}
}