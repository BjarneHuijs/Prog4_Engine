#pragma once
#include "ObserverComponent.h"

namespace Idiot_Engine
{
	class TextObserverComponent : public ObserverComponent
	{
	public:
		explicit TextObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types);


		void OnNotify(const GameObject& object, const ObserverEvent& event) override;

	};
}
