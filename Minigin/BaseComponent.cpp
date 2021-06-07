#include "MiniginPCH.h"
#include "BaseComponent.h"

using namespace Idiot_Engine;
BaseComponent::~BaseComponent()
{
	m_pParent = nullptr;
}

std::string BaseComponent::GetName() const
{
	return m_Name;
}

GameObject* BaseComponent::GetParent() const
{
	return m_pParent;
}

void BaseComponent::SetParent(GameObject* pParent)
{
	if(pParent)
	{
		m_pParent = pParent;
	}
}

BaseComponent::BaseComponent(const std::string& name)
	: m_Name(name)
{}
