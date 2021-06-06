#include "QBertGamePCH.h"
#include "PlayerObserverComponent.h"

#include "GameObject.h"
#include "ObserverComponent.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "../QBertComponent.h"
#include "../../Level/QBertStructs/QBertStructs.h"
#include "../../Level/Tile/Manager/TileManager.h"

using namespace Idiot_Engine;
PlayerObserverComponent::PlayerObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types, const int level)
	: ObserverComponent(name, linkedComponentName, types)
	, m_Level(level)
{}

void PlayerObserverComponent::OnNotify(const GameObject& player, const ObserverEvent& event) // object
{
	for (const EventTypes& type : m_Types) 
	{
		/*const bool playerMoveEvent{ type == EventTypes::MoveBotLeft
		|| type == EventTypes::MoveBotRight
		|| type == EventTypes::MoveTopLeft
		|| type == EventTypes::MoveTopRight };*/
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
							TileStates prevState = tile->CurrentState;
							tile->QBertStep();
							if (static_cast<int>(prevState) < tile->NrOfColors - 1)
								qBert->ChangeColor(tileIdx);
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