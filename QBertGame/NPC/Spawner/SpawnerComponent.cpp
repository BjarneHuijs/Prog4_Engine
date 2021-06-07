#include "QBertGamePCH.h"
#include "SpawnerComponent.h"



#include "GameObject.h"
#include "NPCManager.h"
#include "../NPCBaseComponent.h"
#include "../Coily/CoilyComponent.h"
#include "../Slick_Sam/SlickSamComponent.h"
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
		NPCManager::GetInstance().SpawnNpc(m_Types);
	}
}

void SpawnerComponent::LateUpdate(const float)
{
	auto npcs = NPCManager::GetInstance().GetNpcs();
	for(const auto& npc : npcs)
	{
		auto slimeComp = npc->GetComponentByType<SlimeComponent>();
		if(slimeComp && slimeComp->IsDead())
		{
			NPCManager::GetInstance().RemoveNpc(slimeComp->GetNPC_ID());
		}

		auto slickSamComp = npc->GetComponentByType<SlickSamComponent>();
		if (slickSamComp && slickSamComp->IsDead())
		{
			NPCManager::GetInstance().RemoveNpc(slickSamComp->GetNPC_ID());
		}
		// redo check for other component types if type != slime or slickSam
		auto coilyComp = npc->GetComponentByType<CoilyComponent>();
		if (coilyComp && coilyComp->IsDead())
		{
			NPCManager::GetInstance().RemoveNpc(coilyComp->GetNPC_ID());
		}
	}
}

void SpawnerComponent::Render(const float) const
{
}

void SpawnerComponent::SetNpcTypes(const std::vector<NPCTypes>& types)
{
	m_Types = types;
}
