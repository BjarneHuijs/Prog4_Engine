#include "QBertGamePCH.h"
#include "NPCManager.h"


#include "../../Structs_And_Menu/QBertStructs.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "../Slime/SlimeComponent.h"
#include "../NPCBaseComponent.h"
#include "../../Level/Tile/TileManager.h"
#include "../Coily/CoilyComponent.h"
#include "../Slick_Sam/SlickSamComponent.h"
#include "../UggWrong/UggWrongComponent.h"

NPCManager::NPCManager()
	: m_CurrentLevel(1)
	, m_bCoilyActive(false)
	, m_HighestId(0)
	, m_bPaused(false)
{
}

void NPCManager::SpawnNpc(const std::vector<NPCTypes>& types)
{
	if (!m_bPaused) 
	{
		if (m_bCoilyActive)
		{
			int typeId = rand() % static_cast<int>(types.size() - 1);
			NPCTypes type = types[typeId];
			switch (type) {
			case NPCTypes::Slime:
				SpawnSlime();
				break;
			case NPCTypes::SlickSam:
				SpawnSlickSam();
				break;
			case NPCTypes::UggWrong:
				SpawnUggWrong();
				break;
			default:
				SpawnSlime();
				break;;
			}
		}
		else
		{
			SpawnCoily();
		}
	}
}

std::vector<std::shared_ptr<Idiot_Engine::GameObject>> NPCManager::GetNpcs() const
{
	return m_pNPCs;
}

std::shared_ptr<Idiot_Engine::GameObject> NPCManager::GetNpc(int npcId) const
{
	return m_pNPCs.at(npcId);
}

void NPCManager::SwitchLevel(int level)
{
	ClearAllEnemies();
	m_CurrentLevel = level;
}

void NPCManager::RemoveNpc(int id)
{
	const auto it = std::find_if(m_pNPCs.begin(), m_pNPCs.end(), [this, id](std::shared_ptr<Idiot_Engine::GameObject> npc)
	{
		auto slimeComp = npc->GetComponentByType<SlimeComponent>();
		if(slimeComp)
		{
			return slimeComp->GetNPC_ID() == id;
		}

		auto coilyComp = npc->GetComponentByType<SlimeComponent>();
		if(coilyComp)
		{
			m_bCoilyActive = false;
			return coilyComp->GetNPC_ID() == id;
		}

		auto slickSamComp = npc->GetComponentByType<SlickSamComponent>();
		if(slickSamComp)
		{
			return slickSamComp->GetNPC_ID() == id;
		}
		
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

	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	for(auto tile : tiles)
	{
		tile->npcHostileOnTile = false;
		tile->npcOnTile = false;
	}

	m_pNPCs.clear();
	m_bCoilyActive = false;
}

void NPCManager::ClearAllButCoily()
{

	int coilyTile{};
	for (auto npc : m_pNPCs)
	{
		auto coily = npc->GetComponentByType<CoilyComponent>();
		if (!coily)
		{
			npc->MarkForDelete();
		}
		else 
		{
			coilyTile = coily->GetCurrentTileID();
		}
	}

	auto tiles = TileManager::GetInstance().GetTiles(m_CurrentLevel - 1);
	for (auto tile : tiles)
	{
		if (tile->TileID != coilyTile) 
		{
			tile->npcHostileOnTile = false;
			tile->npcOnTile = false;
		}
	}

	//m_pNPCs.clear();
	//m_bCoilyActive = false;
}

void NPCManager::FreezeNpcs()
{
	for(auto npc : m_pNPCs)
	{
		auto slime = npc->GetComponentByType<SlimeComponent>();
		if (slime)
		{
			slime->Pause();
			continue;;
		}
		
		auto slickSam = npc->GetComponentByType<SlickSamComponent>();
		if (slickSam)
		{
			slickSam->Pause();
			continue;
		}

		auto coily = npc->GetComponentByType<CoilyComponent>();
		if (coily)
		{
			coily->Pause();
			continue;
		}
	}

	m_bPaused = true;
}

void NPCManager::UnPause()
{
	m_bPaused = false;
}

void NPCManager::SpawnSlime()
{
	auto scene = Idiot_Engine::SceneManager::GetInstance().GetActiveScene();
	const float posOffset{ TileManager::GetInstance().GetTile(m_CurrentLevel - 1, 0)->size * 0.25f };

	bool redSlime = (rand() % 4) != 0;
	int spawnTile = (rand() % 2) + 1;

	std::shared_ptr<Idiot_Engine::GameObject> npcObj = std::make_shared<Idiot_Engine::GameObject>();
	std::shared_ptr<SlimeComponent> slime = std::make_shared<SlimeComponent>("slime_" + std::to_string(m_HighestId), redSlime, m_HighestId, spawnTile, m_CurrentLevel);
	const auto slimeSprite = std::make_shared<Idiot_Engine::SpriteComponent>("Slime_" + std::to_string(m_HighestId) + " Sprite", 1);
	m_HighestId++;
	slimeSprite->SetScale(2, 2);
	if (redSlime)
		slimeSprite->SetTexture("RedSlime.png");
	else
		slimeSprite->SetTexture("GreenSlime.png");

	npcObj->AddComponent(slime, slime->GetName());
	npcObj->AddComponent(slimeSprite, slimeSprite->GetName());
	m_pNPCs.push_back(npcObj);
	scene->Add(npcObj);
	slime->SetPosOffset(posOffset);
	const auto startLocation = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, spawnTile)->Position.GetPosition2D();
	npcObj->SetPosition(startLocation.x + posOffset, startLocation.y - (posOffset * 4));
}

void NPCManager::SpawnSlickSam()
{
	auto scene = Idiot_Engine::SceneManager::GetInstance().GetActiveScene();
	const float posOffset{ TileManager::GetInstance().GetTile(m_CurrentLevel - 1, 0)->size * 0.25f };

	bool slick = (rand() % 2) != 0;
	int spawnTile = (rand() % 2) + 1;

	std::shared_ptr<Idiot_Engine::GameObject> npcObj = std::make_shared<Idiot_Engine::GameObject>();
	std::shared_ptr<SlickSamComponent> slickSam = std::make_shared<SlickSamComponent>("SlickSam_" + std::to_string(m_HighestId), m_HighestId, slick, spawnTile, m_CurrentLevel);
	const auto slickSamSprite = std::make_shared<Idiot_Engine::SpriteComponent>("SlickSam_" + std::to_string(m_HighestId) + " Sprite", 1);
	m_HighestId++;
	slickSamSprite->SetScale(2, 2);
	if (slick)
		slickSamSprite->SetTexture("Slick.png");
	else
		slickSamSprite->SetTexture("Sam.png");

	npcObj->AddComponent(slickSam, slickSam->GetName());
	npcObj->AddComponent(slickSamSprite, slickSamSprite->GetName());
	m_pNPCs.push_back(npcObj);
	scene->Add(npcObj);
	slickSam->SetPosOffset(posOffset);
	const auto startLocation = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, spawnTile)->Position.GetPosition2D();
	npcObj->SetPosition(startLocation.x + posOffset, startLocation.y - (posOffset * 4));
}

void NPCManager::SpawnCoily()
{
	auto scene = Idiot_Engine::SceneManager::GetInstance().GetActiveScene();
	const float posOffset{ TileManager::GetInstance().GetTile(m_CurrentLevel - 1, 0)->size * 0.25f };

	int spawnTile = (rand() % 2) + 1;

	std::shared_ptr<Idiot_Engine::GameObject> npcObj = std::make_shared<Idiot_Engine::GameObject>();
	std::shared_ptr<CoilyComponent> coily = std::make_shared<CoilyComponent>("Coily_" + std::to_string(m_HighestId), m_HighestId, spawnTile, m_CurrentLevel);
	const auto coilySprite = std::make_shared<Idiot_Engine::SpriteComponent>("Coily_" + std::to_string(m_HighestId) + " Sprite", 1);
	m_HighestId++;
	//coilySprite->SetScale(2, 2);

	coilySprite->SetTexture("Egg.png");

	npcObj->AddComponent(coily, coily->GetName());
	npcObj->AddComponent(coilySprite, coilySprite->GetName());
	m_pNPCs.push_back(npcObj);
	scene->Add(npcObj);
	coily->SetPosOffset(posOffset);
	const auto startLocation = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, spawnTile)->Position.GetPosition2D();
	npcObj->SetPosition(startLocation.x + posOffset, startLocation.y - (posOffset));

	m_bCoilyActive = true;
}

void NPCManager::SpawnUggWrong()
{
	auto scene = Idiot_Engine::SceneManager::GetInstance().GetActiveScene();
	const float posOffset{ TileManager::GetInstance().GetTile(m_CurrentLevel - 1, 0)->size * 0.5f };

	bool isUgg = (rand() % 2) != 0;
	int spawnTile;

	// Manually defined bottom left/bottom right tile Id's here since the level is always the same size
	if (isUgg)
		spawnTile = 27;
	else
		spawnTile = 21;
	
	std::shared_ptr<Idiot_Engine::GameObject> npcObj = std::make_shared<Idiot_Engine::GameObject>();
	std::shared_ptr<UggWrongComponent> uggWrong = std::make_shared<UggWrongComponent>("UggWrong_" + std::to_string(m_HighestId), isUgg, m_HighestId, spawnTile, m_CurrentLevel);
	const auto uggWrongSprite = std::make_shared<Idiot_Engine::SpriteComponent>("UggWrong_" + std::to_string(m_HighestId) + " Sprite", 1);
	m_HighestId++;
	uggWrongSprite->SetScale(2, 2);
	if (isUgg)
		uggWrongSprite->SetTexture("Ugg.png");
	else
		uggWrongSprite->SetTexture("WrongWay.png");

	npcObj->AddComponent(uggWrong, uggWrong->GetName());
	npcObj->AddComponent(uggWrongSprite, uggWrongSprite->GetName());
	m_pNPCs.push_back(npcObj);
	scene->Add(npcObj);
	uggWrong->SetPosOffset(posOffset);
	const auto startLocation = TileManager::GetInstance().GetTile(m_CurrentLevel - 1, spawnTile)->Position.GetPosition2D();
	if(isUgg)
		npcObj->SetPosition(startLocation.x + posOffset, startLocation.y + (posOffset));
	else
		npcObj->SetPosition(startLocation.x - posOffset, startLocation.y + (posOffset));
}
