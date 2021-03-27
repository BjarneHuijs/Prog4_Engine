#include "MiniginPCH.h"
#include "ObserverComponent.h"

Idiot_Engine::ObserverComponent::ObserverComponent(const std::string& name, EventTypes type)
	: BaseComponent(name)
	, m_Type(type)
{}
