#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace Idiot_Engine
{
	class ObserverComponent : public BaseComponent
	{
	public:
		ObserverComponent(const std::string& name, EventTypes type);
		//virtual ~ObserverComponent() = default;
		
		virtual void OnNotify(const GameObject& object, const Event& event) = 0;

		void FixedUpdate(const float) override{}; //deltaTime
		void Update(const float) override{}; //deltaTime
		void LateUpdate(const float) override {}; //deltaTime
		void Render(const float) const override {}; //nextFrame
	
	protected:
		EventTypes m_Type{};
	};
}