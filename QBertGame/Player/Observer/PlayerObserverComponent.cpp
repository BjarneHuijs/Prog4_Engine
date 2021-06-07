#include "QBertGamePCH.h"
#include "PlayerObserverComponent.h"

#include "GameObject.h"
#include "ObserverComponent.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "../QBertComponent.h"
#include "../../Structs_And_Menu/QBertStructs.h"
#include "../../Level/Tile/TileManager.h"
#include "../../NPC/Coily/CoilyComponent.h"
#include "../../NPC/Slick_Sam/SlickSamComponent.h"
#include "../../NPC/Slime/SlimeComponent.h"
#include "../../NPC/Spawner/NPCManager.h"

using namespace Idiot_Engine;
PlayerObserverComponent::PlayerObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types, const int level)
	: ObserverComponent(name, linkedComponentName, types)
	, m_Level(level)
{}

void PlayerObserverComponent::OnNotify(const GameObject& player, const ObserverEvent& event) // object
{
	for (const EventTypes& type : m_Types) 
	{
		if (m_pParent && event.type == type)
		{
			auto qBert = player.GetComponentByName<QBertComponent>(m_LinkedComponentName);
			auto spriteComponent{ m_pParent->GetComponentByType<SpriteComponent>() };
			if (qBert) 
			{
				std::string spriteName{ spriteComponent->GetName() };
				
				// add 1 to index to find value of index in name
				const auto delimitPos{ spriteName.find_first_of('_') + 1 };
				const std::string tileType{ spriteName.substr(0, delimitPos - 1) };
				const auto tileIdx{ std::stoi(spriteName.substr(delimitPos)) };
				auto tile = TileManager::GetInstance().GetTile(qBert->GetCurrentLevelNr() - 1, tileIdx);
				
				if (m_Level == tile->LevelNr)
				{
					auto discs = TileManager::GetInstance().GetDiscs(qBert->GetCurrentLevelNr() - 1);
					if (tileType._Equal("DiscSprite")) 
					{
						const auto discIdx{ std::stoi(spriteName.substr(delimitPos)) };
						for (DiscData* disc : discs)
						{
							if (qBert->GetDiscId() == disc->DiscID && discIdx == disc->DiscID && disc->LevelNr == m_Level && !disc->Used)
							{
								disc->QBertStep();
								const int targetFrame = static_cast<int>(disc->CurrentState);
								spriteComponent->ToTargetFrame(targetFrame);
								break;
							}
							const int targetFrame = static_cast<int>(disc->CurrentState);
							spriteComponent->ToTargetFrame(targetFrame);
						}
					}
					else 
					{
						if (spriteComponent && tileIdx == qBert->GetCurrentTileID() && qBert->GetNrOfLives() > 0)
						{
							if(tile->npcHostileOnTile)
							{
								if (qBert->IsOnDisc())
								{
									auto npcs = NPCManager::GetInstance().GetNpcs();
									for (std::shared_ptr<GameObject> npc : npcs)
									{
										const std::shared_ptr<CoilyComponent> coily = npc->GetComponentByType<CoilyComponent>();
										if (coily && coily->GetCurrentLevelNr() == m_Level)
										{
											qBert->KillCoilyWithDisc();
										}
									}
									
									tile->npcHostileOnTile = false;
									NPCManager::GetInstance().ClearAllEnemies();
								}
								else 
								{
									ServiceLocator::GetAudio()->QueueSound(8); // id 8 = swear
									qBert->Kill();
									tile->npcHostileOnTile = false;
									NPCManager::GetInstance().ClearAllEnemies();
								}
							}
							else if(tile->npcOnTile)
							{
								//qBert->CatchNPC();

								auto npcs = NPCManager::GetInstance().GetNpcs();
								for(std::shared_ptr<GameObject> npc : npcs)
								{
									// green slime handling
									const std::shared_ptr<SlimeComponent> slime = npc->GetComponentByType<SlimeComponent>();
									if (slime && slime->GetCurrentLevelNr() == m_Level && slime->GetCurrentTileID() == qBert->GetCurrentTileID()) 
									{
										tile->npcOnTile = false;
										NPCManager::GetInstance().FreezeNpcs();
										NPCManager::GetInstance().RemoveNpc(slime->GetNPC_ID());
										qBert->CatchNPC();
									}

									// slick/sam handling
									const std::shared_ptr<SlickSamComponent> slickSam = npc->GetComponentByType<SlickSamComponent>();
									if (slickSam && slickSam->GetCurrentLevelNr() == m_Level && slickSam->GetCurrentTileID() == qBert->GetCurrentTileID())
									{
										tile->npcOnTile = false;
										NPCManager::GetInstance().RemoveNpc(slickSam->GetNPC_ID());
										qBert->CatchNPC();
									}

								}
							}
							else 
							{
								auto npcs = NPCManager::GetInstance().GetNpcs();
								for (std::shared_ptr<GameObject> npc : npcs)
								{
									// inform coily of player pos
									const std::shared_ptr<CoilyComponent> coily = npc->GetComponentByType<CoilyComponent>();
									if (coily && coily->GetCurrentLevelNr() == m_Level)
									{
										coily->SetQBertTile(tile->TileID);
										if(!coily->IsEgg())
											coily->GetParent()->GetComponentByType<SpriteComponent>()->SetTexture("Coily.png");
									}
								}
								TileStates prevState = tile->CurrentState;
								tile->QBertStep();
								if (static_cast<int>(prevState) < tile->NrOfColors - 1)
									qBert->ChangeColor(tileIdx);
							}
						}

						const int offset = ((tile->LevelNr - 1) * tile->FramesPerLevel);
						const int targetFrame = offset + static_cast<int>(tile->CurrentState);
						spriteComponent->ToTargetFrame(targetFrame);
					}
				}
			}
		}
	}
}