#include "MiniginPCH.h"
#include "Command.h"

Idiot_Engine::Command::Command(GameObject* object)
	: m_pObject(object)
{}

Idiot_Engine::Command::~Command()
{
	m_pObject = nullptr;
}
