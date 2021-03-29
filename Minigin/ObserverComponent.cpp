#include "MiniginPCH.h"
#include "ObserverComponent.h"

Idiot_Engine::ObserverComponent::ObserverComponent(const std::string& name, const std::string& linkedComponentName, EventTypes type)
	: BaseComponent(name)
	, m_Type(type)
	, m_LinkedComponentName(linkedComponentName)
{}
