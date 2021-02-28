#include "MiniginPCH.h"
#include "Command.h"

dae::Command::Command(GameObject* object)
	: m_pObject(object)
{}

dae::Command::~Command()
{
	m_pObject = nullptr;
}
