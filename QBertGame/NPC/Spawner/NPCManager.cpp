#include "QBertGamePCH.h"
#include "NPCManager.h"


#include "../../QBertStructs/QBertStructs.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "../Slime/SlimeComponent.h"
#include "../NPCBaseComponent.h"
#include "../../Level/Tile/TileManager.h"

NPCManager::NPCManager()
	: m_CurrentLevel(1)
	, m_bCoilyActive(false)
	, m_HighestId(0)
{
}

void NPCManager::SpawnNpc()
{
	const float posOffset{ TileManager::GetInstance().GetTile(m_CurrentLevel - 1, 0)->size * 0.25f };

	auto scene = Idiot_Engine::SceneManager::GetInstance().GetActiveScene();
	//const int npcID{ static_cast<int>(m_pNPCs.size()) - 1 };
	if(!m_bCoilyActive)
	{
		bool redSlime = (rand() % 10) == 0;
		int spawnTile = (rand() % 2) + 1;
		// spawn other npc's
		std::shared_ptr<Idiot_Engine::GameObject> npcObj = std::make_shared<Idiot_Engine::GameObject>();
		std::shared_ptr<SlimeComponent> slime = std::make_shared<SlimeComponent>("slime_" + std::to_string(m_HighestId), m_HighestId, redSlime, spawnTile, m_CurrentLevel);
		const auto slimeSprite = std::make_shared<Idiot_Engine::SpriteComponent>("Slime_" + std::to_string(m_HighestId) + " Sprite", 1);
		m_HighestId++;
		slimeSprite->SetScale(2, 2);
		if(redSlime)
			slimeSprite->SetTexture("RedSlime.png");
		else
			slimeSprite->SetTexture("GreenSlime.png");

		npcObj->AddComponent(slime, slime->GetName());
		npcObj->AddComponent(slimeSprite, slimeSprite->GetName());
		m_pNPCs.push_back(npcObj);
		scene->Add(npcObj);
		slime->SetPosOffset(posOffset);
		auto startLocation = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, spawnTile)->Position.GetPosition2D();
		npcObj->SetPosition(startLocation.x + posOffset, startLocation.y - (posOffset * 4));
	}else
	{
		// spawn coily
	}
}

std::vector<std::shared_ptr<Idiot_Engine::GameObject>> NPCManager::GetNpcs() const
{
	return m_pNPCs;
}

void NPCManager::SwitchLevel(int level)
{
	ClearAllEnemies();
	m_CurrentLevel = level;
}

void NPCManager::RemoveNpc(int id)
{
	const auto it = std::find_if(m_pNPCs.begin(), m_pNPCs.end(), [id](std::shared_ptr<Idiot_Engine::GameObject> npc)
	{
		auto slimeComp = npc->GetComponentByType<SlimeComponent>();
		if(slimeComp)
		{
			return slimeComp->GetNPC_ID() == id;
		}

		/*auto coilyComp = npc->GetComponentByType<SlimeComponent>();
		if(coilyComp)
		{
			return coilyComp->GetNPC_ID() == id;
		}*/

		/*auto slickSamComp = npc->GetComponentByType<SlimeComponent>();
		if(slickSamComp)
		{
			return slickSamComp->GetNPC_ID() == id;
		}*/
		
		return false;
	});

	if(it != m_pNPCs.end())
	{
		//std::remove(m_pNPCs.begin(), m_pNPCs.end(), it);
		//it->reset();
		it->get()->MarkForDelete();
		m_pNPCs.erase(it);
	}
}

void NPCManager::ClearAllEnemies()
{
	for(auto npc : m_pNPCs)
	{
		npc->MarkForDelete();
	}
}
