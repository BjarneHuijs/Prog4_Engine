#pragma once
#include "GameObject.h"
#include "PlayerComponent.h"

namespace dae
{
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

	class Kill : public Command
	{
	public:
		explicit Kill(GameObject* object) : Command(object){}
		void Execute() override { GetActor()->GetComponent<PlayerComponent>()->Kill(); }
	};
}
