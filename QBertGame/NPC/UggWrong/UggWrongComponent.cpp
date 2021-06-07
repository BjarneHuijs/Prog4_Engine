#include "QBertGamePCH.h"
#include "UggWrongComponent.h"

#include "../../Level/Levels/GameLevels.h"
#include "GameObject.h"
#include "SubjectComponent.h"
#include "../../Level/Tile/TileManager.h"
#include "../Spawner/NPCManager.h"

using namespace Idiot_Engine;
UggWrongComponent::UggWrongComponent(const std::string& name, bool isUgg, int id, int spawnTile, int level, float movementSpeed)
	: NPCBaseComponent(name, id, spawnTile, level, movementSpeed)
	, m_bIsUgg(isUgg)

{
	m_TargetPos = TileManager::GetInstance().GetTile(level - 1, spawnTile)->Position.GetPosition2D();
}

void UggWrongComponent::FixedUpdate(const float)
{}

void UggWrongComponent::Update(const float deltaTime)
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
		const Transform transform{ m_pParent->GetTransform() };
		if (m_pParent)
		{
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
				if(m_bIsUgg)
				{
					if (nextMove == 0)
					{
						MoveTopLeft();
					}
					else
					{
						MoveBotLeft();
					}
				}
				else 
				{
					if (nextMove == 0)
					{
						MoveTopRight();
					}
					else
					{
						MoveBotRight();
					}
				}
			}
		}
	}
}

void UggWrongComponent::LateUpdate(const float)
{}

void UggWrongComponent::Render(const float) const
{}

void UggWrongComponent::Kill()
{
	ServiceLocator::GetAudio()->QueueSound(4); // id 4 = fall
	m_bDead = true;
}

void UggWrongComponent::Fall()
{
	m_bFalling = true;
}

void UggWrongComponent::MoveTopLeft()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->TopLeft };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);

		tile->npcHostileOnTile = false;

		if (targetIndex == -1)
		{
			Fall();
		}
		else
		{

			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			if (m_bIsUgg)
			{
				m_TargetPos.x += m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}
			else
			{
				m_TargetPos.x -= m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}

void UggWrongComponent::MoveTopRight()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->TopRight };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);

		tile->npcHostileOnTile = false;

		if (targetIndex == -1)
		{
			Fall();
		}
		else
		{

			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			if (m_bIsUgg)
			{
				m_TargetPos.x += m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}
			else
			{
				m_TargetPos.x -= m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}

void UggWrongComponent::MoveBotLeft()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotLeft };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
		tile->npcHostileOnTile = false;

		if (!(targetIndex == -1))
		{
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			if (m_bIsUgg)
			{
				m_TargetPos.x += m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}
			else
			{
				m_TargetPos.x -= m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}

void UggWrongComponent::MoveBotRight()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotRight };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);

		tile->npcHostileOnTile = false;
		
		if (!(targetIndex == -1))
		{
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			if (m_bIsUgg) 
			{
				m_TargetPos.x += m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}
			else 
			{
				m_TargetPos.x -= m_PosOffset;
				m_TargetPos.y += (m_PosOffset);
			}

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}