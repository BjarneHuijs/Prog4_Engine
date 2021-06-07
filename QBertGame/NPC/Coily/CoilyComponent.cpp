#include "QBertGamePCH.h"
#include "CoilyComponent.h"

#include "../../Level/Levels/GameLevels.h"
#include "GameObject.h"
#include "SubjectComponent.h"
#include "../../Level/Tile/TileManager.h"
#include "../Spawner/NPCManager.h"

using namespace Idiot_Engine;
CoilyComponent::CoilyComponent(const std::string& name, int id, int spawnTile, int level, float movementSpeed)
	: NPCBaseComponent(name, id, spawnTile, level, movementSpeed)
	, m_bEgg(true)
	, m_QBertTile(0)

{
	m_TargetPos = TileManager::GetInstance().GetTile(level - 1, spawnTile)->Position.GetPosition2D();
}

void CoilyComponent::FixedUpdate(const float)
{}

void CoilyComponent::Update(const float deltaTime)
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

				if (m_TargetPos.y > 600)
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
				if(m_bEgg)
				{
					const int nextMove = rand() % 2;
					const auto currentTile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
					if (nextMove == 0 && currentTile->BotLeft != -1)
					{
						MoveBotLeft();
					}
					else if(currentTile->BotRight != -1)
					{
						MoveBotRight();
					}else if(currentTile->BotLeft == -1 && currentTile->BotRight == -1)
					{
						m_bEgg = false;
					}
				}
				else
				{
					TileManager& tileManager = TileManager::GetInstance();
					
					TileData* qBertTile = tileManager.GetTile(m_CurrentLevel - 1, m_QBertTile);
					TileData* coilyTile = tileManager.GetTile(m_CurrentLevel - 1, m_CurrentTile);
					TileData* tl = tileManager.GetTile(m_CurrentLevel - 1, coilyTile->TopLeft);
					TileData* tr = tileManager.GetTile(m_CurrentLevel - 1, coilyTile->TopRight);
					TileData* bl = tileManager.GetTile(m_CurrentLevel - 1, coilyTile->BotLeft);
					TileData* br = tileManager.GetTile(m_CurrentLevel - 1, coilyTile->BotRight);

					float tlLength{};
					float trLength{};
					float blLength{};
					float brLength{};

					if (tl)
						tlLength = glm::length(tl->Position.GetPosition2D() - qBertTile->Position.GetPosition2D());
					else 
						tlLength = static_cast<float>(INT_MAX);
					if (tr)
						trLength = glm::length(tr->Position.GetPosition2D() - qBertTile->Position.GetPosition2D());
					else 
						trLength = static_cast<float>(INT_MAX);
					
					if (bl)
						blLength = glm::length(bl->Position.GetPosition2D() - qBertTile->Position.GetPosition2D());
					else
						blLength = static_cast<float>(INT_MAX);

					if (br)
						brLength = glm::length(br->Position.GetPosition2D() - qBertTile->Position.GetPosition2D());
					else
						brLength = static_cast<float>(INT_MAX);
					
					
					float distance = std::min(tlLength, trLength);
					distance = std::min(distance, blLength);
					distance = std::min(distance, brLength);
					
					if (distance == tlLength)
						MoveTopLeft();
					else if (distance == trLength)
						MoveTopRight();
					else if (distance == blLength)
						MoveBotLeft();
					else if (distance == brLength)
						MoveBotRight();
					
				}
			}
		}
	}
}

void CoilyComponent::LateUpdate(const float)
{}

void CoilyComponent::Render(const float) const
{
}

void CoilyComponent::Kill()
{
	ServiceLocator::GetAudio()->QueueSound(4); // id 4 = fall
	m_bDead = true;
}

void CoilyComponent::Fall()
{
	m_bFalling = true;
}

void CoilyComponent::MoveTopLeft()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->TopLeft };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(2); // id 2 = moveCoily
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
		tile->npcHostileOnTile = false;

		if (targetIndex == -1 && !m_bEgg)
		{
			Fall();
		}
		else if(!m_bEgg)
		{
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset);

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}
void CoilyComponent::MoveTopRight()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->TopRight };
	if (!m_bMoving)
	{
		ServiceLocator::GetAudio()->QueueSound(2); // id 2 = moveCoily
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
		tile->npcHostileOnTile = false;

		if (targetIndex == -1 && !m_bEgg)
		{
			Fall();
		}
		else if(!m_bEgg)
		{
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset);

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}

void CoilyComponent::MoveBotLeft()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotLeft };
	if (!m_bMoving)
	{
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
		tile->npcHostileOnTile = false;

		/*if (targetIndex == -1 && m_bEgg)
		{
			m_bEgg = false;
			m_TargetPos = tiles[m_CurrentTile]->Position.GetPosition2D();
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset / 4);
			
			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		else */if (targetIndex == -1)
		{
			Fall();
		}
		else
		{
			if (m_bEgg)
				ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
			else
				ServiceLocator::GetAudio()->QueueSound(2); // id 2 = moveCoily
			
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset);

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}

void CoilyComponent::MoveBotRight()
{
	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	const int targetIndex{ tiles[m_CurrentTile]->BotRight };
	if (!m_bMoving)
	{
		TileData* tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
		tile->npcHostileOnTile = false;

		/*if (targetIndex == -1 && m_bEgg)
		{
			m_bEgg = false;
			m_TargetPos = tiles[m_CurrentTile]->Position.GetPosition2D();
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset / 4);

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		else */if(targetIndex == -1)
		{
			Fall();
		}
		else
		{
			if(m_bEgg)
				ServiceLocator::GetAudio()->QueueSound(3); // id 3 = moveSlime
			else
				ServiceLocator::GetAudio()->QueueSound(2); // id 2 = moveCoily
			
			m_TargetPos = tiles[targetIndex]->Position.GetPosition2D();
			m_CurrentTile = targetIndex;
			m_TargetPos.x += m_PosOffset;
			m_TargetPos.y -= (m_PosOffset);

			tile = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, m_CurrentTile);
			tile->npcHostileOnTile = true;
		}
		m_bMoving = true;
	}
}

void CoilyComponent::SetQBertTile(int tileId)
{
	m_QBertTile = tileId;
}

bool CoilyComponent::IsEgg() const
{
	return m_bEgg;
}
