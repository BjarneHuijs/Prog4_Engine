#pragma once
#include "ObserverComponent.h"

namespace Idiot_Engine
{
	class TextObserverComponent : public ObserverComponent
	{
	public:
		explicit TextObserverComponent(const std::string& name, EventTypes type);


		void OnNotify(const GameObject& object, const Event& event) override;

	};
}
