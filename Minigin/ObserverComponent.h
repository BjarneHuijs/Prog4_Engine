#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace Idiot_Engine
{
	class ObserverComponent : public BaseComponent
	{
	public:
		ObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types = {std::vector<EventTypes>()});
		//virtual ~ObserverComponent() = default;
		
		virtual void OnNotify(const GameObject& object, const ObserverEvent& event) = 0;

		void FixedUpdate(const float) override{}; //deltaTime
		void Update(const float) override{}; //deltaTime
		void LateUpdate(const float) override {}; //deltaTime
		void Render(const float) const override {}; //nextFrame
	
	protected:
		std::vector<EventTypes> m_Types{};
		std::string m_LinkedComponentName{};
	};
}