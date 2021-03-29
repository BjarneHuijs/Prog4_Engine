#include "MiniginPCH.h"
#include "TextObserverComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace Idiot_Engine;
TextObserverComponent::TextObserverComponent(const std::string& name, const std::string& linkedComponentName, EventTypes type)
	: ObserverComponent(name, linkedComponentName, type)
{}

void TextObserverComponent::OnNotify(const GameObject&, const ObserverEvent& event) // object
{
	if (m_pParent && event.type == m_Type)
	{
		
		auto component{ m_pParent->GetComponentByName<TextComponent>(m_LinkedComponentName) };
		
		if(component)
			component->SetText(event.message);
	}
}
