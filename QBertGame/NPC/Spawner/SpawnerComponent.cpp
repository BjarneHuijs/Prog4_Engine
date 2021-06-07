#include "QBertGamePCH.h"
#include "SpawnerComponent.h"



#include "GameObject.h"
#include "NPCManager.h"
#include "../NPCBaseComponent.h"
#include "../Slime/SlimeComponent.h"


SpawnerComponent::SpawnerComponent(const std::string& name, int interval)
	: BaseComponent(name)
	, m_SpawnInterval(static_cast<float>(interval))
	, m_SpawnTimer(interval / 2.f)
{
	
}

//void SpawnerComponent::SetSpawnInterval(float interval)
//{
//	m_SpawnInterval = interval;
//}


void SpawnerComponent::FixedUpdate(const float)
{
}

void SpawnerComponent::Update(const float deltaTime)
{
	m_SpawnTimer += deltaTime;
	if (m_SpawnTimer >= m_SpawnInterval)
	{
		m_SpawnTimer = 0;
		NPCManager::GetInstance().SpawnNpc();
	}
}

void SpawnerComponent::LateUpdate(const float)
{
	auto npcs = NPCManager::GetInstance().GetNpcs();
	for(const auto& npc : npcs)
	{
		auto npcComp = npc->GetComponentByType<SlimeComponent>();
		if(npcComp->IsDead())
		{
			NPCManager::GetInstance().RemoveNpc(npcComp->GetNPC_ID());
		}

		// redo check for other component types if type != slime
	}
}

void SpawnerComponent::Render(const float) const
{
}