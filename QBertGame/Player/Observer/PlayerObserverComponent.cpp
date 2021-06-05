#include "QBertGamePCH.h"
#include "PlayerObserverComponent.h"

#include "GameObject.h"
#include "ObserverComponent.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "../QBertComponent.h"

using namespace Idiot_Engine;
PlayerObserverComponent::PlayerObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types)
	: ObserverComponent(name, linkedComponentName, types)
{}

void PlayerObserverComponent::OnNotify(const Idiot_Engine::GameObject& tile, const ObserverEvent& event) // object
{
	for (const EventTypes& type : m_Types) 
	{
		const bool playerMoveEvent{ type == EventTypes::MoveBotLeft
		|| type == EventTypes::MoveBotRight
		|| type == EventTypes::MoveTopLeft
		|| type == EventTypes::MoveTopRight };
		if (m_pParent && playerMoveEvent && event.type == type)
		{
			//m_pParent->GetComponentByName<QBertComponent>(m_LinkedComponentName);
			auto spriteComponent{ tile.GetComponentByType<Idiot_Engine::SpriteComponent>() };
			
			if (spriteComponent)
				spriteComponent->ToNextFrame();
		}
	}
}