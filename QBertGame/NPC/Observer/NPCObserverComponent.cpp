#include "QBertGamePCH.h"
#include "NPCObserverComponent.h"

#include "GameObject.h"
#include "ObserverComponent.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "../../Player/QBertComponent.h"
#include "../../QBertStructs/QBertStructs.h"
#include "../../Level/Tile/TileManager.h"

using namespace Idiot_Engine;
NPCObserverComponent::NPCObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types, const int level)
	: ObserverComponent(name, linkedComponentName, types)
	, m_Level(level)
{}

void NPCObserverComponent::OnNotify(const GameObject& player, const ObserverEvent& event) // object
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
					// npcs = manager.getNpcs
					// for enemy : enemies
					// if(playerPos == nps pos { call collision hit)
					
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