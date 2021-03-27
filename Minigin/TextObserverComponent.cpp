#include "MiniginPCH.h"
#include "TextObserverComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace Idiot_Engine;
TextObserverComponent::TextObserverComponent(const std::string& name, EventTypes type)
	: ObserverComponent(name, type)
{}

void TextObserverComponent::OnNotify(const GameObject&, const Event& event) // object
{
	if (m_pParent && event.type == m_Type)
	{
		auto component{ m_pParent->GetComponentByName<TextComponent>(m_Name) };
		
		if(component) component->SetText(event.message);
	}
}
