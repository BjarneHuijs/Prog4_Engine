#pragma once
#include "GameObject.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"

namespace Idiot_Engine
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
		void Execute() override
		{
			GetActor()->GetComponentByType<PlayerComponent>()->Kill();
			ServiceLocator::GetAudio()->QueueSound(0); // id 0 = kill player
		}
	};

	class KillCoily : public Command
	{
	public:
		explicit KillCoily(GameObject* object) : Command(object){}
		void Execute() override
		{
			GetActor()->GetComponentByType<PlayerComponent>()->KillCoilyWithDisc();
			ServiceLocator::GetAudio()->QueueSound(1); // id 1 = kill coily
		}
	};

	class ChangeColor : public Command
	{
	public:
		explicit ChangeColor(GameObject* object) : Command(object){}
		void Execute() override { GetActor()->GetComponentByType<PlayerComponent>()->ChangeColor(); }
	};

	class CalculateRemainingDiscs : public Command
	{
	public:
		explicit CalculateRemainingDiscs(GameObject* object) : Command(object) {}
		void Execute() override { GetActor()->GetComponentByType<PlayerComponent>()->RemainingDiscsScore(); }
	};

	class CatchNPC : public Command
	{
	public:
		explicit CatchNPC(GameObject* object) : Command(object) {}
		void Execute() override { GetActor()->GetComponentByType<PlayerComponent>()->CatchNPC(); }
	};
}
