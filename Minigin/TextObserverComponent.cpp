#include "MiniginPCH.h"
#include "TextObserverComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace Idiot_Engine;
TextObserverComponent::TextObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types)
	: ObserverComponent(name, linkedComponentName, types)
{
	UNREFERENCED_PARAMETER(types);
}

void TextObserverComponent::OnNotify(const GameObject&, const ObserverEvent& event) // object
{
	for (const EventTypes& type : m_Types) 
	{
		if (m_pParent && event.type == type)
		{

			auto component{ m_pParent->GetComponentByName<TextComponent>(m_LinkedComponentName) };

			if (component)
				component->SetText(event.message);
		}
	}
}
