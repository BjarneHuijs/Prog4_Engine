#include "QBertGamePCH.h"
#include "SlickSamComponent.h"

#include "../../Level/Levels/GameLevels.h"
#include "GameObject.h"
#include "SubjectComponent.h"
#include "../../Level/Tile/TileManager.h"
#include "../Spawner/NPCManager.h"

using namespace Idiot_Engine;
SlickSamComponent::SlickSamComponent(const std::string& name, bool isSlick, int id, int spawnTile, int level, float movementSpeed)
	: NPCBaseComponent(name, id, spawnTile, level, movementSpeed)
	, m_bSlick(isSlick)

{
	m_TargetPos = TileManager::GetInstance().GetTile(level - 1, spawnTile)->Position.GetPosition2D();
}

void SlickSamComponent::FixedUpdate(const float)
{}

void SlickSamComponent::Update(const float deltaTime)
{
	if (m_bPaused)
	{
		m_PauseTimer += deltaTime;
		if (m_PauseTimer >= m_PauseTime)
		{
			NPCManager::GetInstance().UnPause();
			m_bPaused = false;
			m_PauseTimer = 0.f;
		}
	}
	else if (m_bMoved)
	{
		m_MoveDelayTimer += deltaTime;
		if (m_MoveDelayTimer >= m_MoveDelay)
		{
			m_bMoved = false;
			m_MoveDelayTimer = 0.f;
		}
	}
	else
	{
		std::shared_ptr<SubjectComponent> subject{ nullptr };
		const Transform transform{ m_pParent->GetTransform() };
		if (m_pParent)
		{
			if (m_bFalling)
			{
				m_TargetPos.y += (m_PosOffset / 4);

				if (m_TargetPos.y > 400)
				{
					m_bDead = true;
					//m_pParent->MarkForDelete();
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
					m_bMoved = true;
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
		}
	}
}

void SlickSamComponent::LateUpdate(const float)
{}

void SlickSamComponent::Render(const float) const
{
}

void SlickSamComponent::Kill()
{
	ServiceLocator::GetAudio()->QueueSound(4); // id 4 = fall
	m_bDead = true;
}

void SlickSamComponent::Fall()
{
	m_bFalling = true;
}

void SlickSamComponent::MoveTopLeft() {}
void SlickSamComponent::MoveTopRight() {}

void SlickSamComponent::MoveBotLeft()
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
			tile->SlickSamStep();
		}
		m_bMoving = true;
	}
}

void SlickSamComponent::MoveBotRight()
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
			tile->SlickSamStep();
		}
		m_bMoving = true;
	}
}