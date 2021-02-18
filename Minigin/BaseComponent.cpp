#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::~BaseComponent()
{
	m_pParent = nullptr;
}