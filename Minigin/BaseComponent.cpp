#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::~BaseComponent()
{
	m_pParent = nullptr;
}

void dae::BaseComponent::SetParent(GameObject* pParent)
{
	if(pParent)
	{
		m_pParent = pParent;
	}
}