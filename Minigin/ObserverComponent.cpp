#include "MiniginPCH.h"
#include "ObserverComponent.h"

Idiot_Engine::ObserverComponent::ObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types)
	: BaseComponent(name)
	, m_Types(types)
	, m_LinkedComponentName(linkedComponentName)
{}
