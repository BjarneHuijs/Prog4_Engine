#include "QBertGamePCH.h"
#include "NPCBaseComponent.h"

NPCBaseComponent::NPCBaseComponent(const std::string& name, int id, int spawnTile, int level, float movementSpeed)
	: BaseComponent(name)
	, m_NPC_ID(id)
	, m_CurrentTile(spawnTile)
	, m_CurrentLevel(level)
	, m_TargetPos()
	, m_MovementSpeed(movementSpeed)
	, m_PosOffset()
	, m_bMoving(true)
	, m_bFalling(false)
	, m_bPaused(false)
	, m_PauseTime(2.f)
	, m_PauseTimer()
	, m_bDead(false)
{
}

void NPCBaseComponent::SetPosOffset(float offset)
{
	m_PosOffset = offset;
}

int NPCBaseComponent::GetCurrentTileID() const
{
	return m_CurrentTile;
}

int NPCBaseComponent::GetCurrentLevelNr() const
{
	return m_CurrentLevel;
}

int NPCBaseComponent::GetNPC_ID() const
{
	return m_NPC_ID;
}

int NPCBaseComponent::IsDead() const
{
	return m_bDead;
}
