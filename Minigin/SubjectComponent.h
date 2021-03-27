#pragma once
#include <vector>


#include "BaseComponent.h"
#include "Structs.h"

namespace Idiot_Engine
{
	class GameObject;
	class ObserverComponent;
	class SubjectComponent : public BaseComponent
	{
	public:
		SubjectComponent(const std::string& name);
		
		void AddObserver(ObserverComponent* pObserver);
		void RemoveObserver(ObserverComponent* pObserver);
	//protected:
		void NotifyObservers(const GameObject& object, const Event& event);

		void FixedUpdate(const float) override {}; //deltaTime
		void Update(const float) override{}; //deltaTime
		void LateUpdate(const float) override{}; //deltaTime
		void Render(const float) const override{}; //nextFrame
	private:
		std::vector<ObserverComponent*> m_pObservers{};
		//int m_NumObservers{};

	};
}