#pragma once
#include "GameObject.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"

namespace Idiot_Engine
{
	// Can be renamed to event?
	
	class Command
	{
	protected:
		GameObject* GetActor() { return m_pObject; }
	public:
		explicit Command(GameObject* object);
		virtual ~Command();
		virtual void Execute() = 0;
	private:

		GameObject* m_pObject;
	};
}
