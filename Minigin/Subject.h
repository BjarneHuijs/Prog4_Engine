#pragma once
#include <vector>

#include "Structs.h"

namespace dae
{
	class GameObject;
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
	protected:
		void NotifyObservers(const GameObject& object, Event event);
	private:
		std::vector<Observer*> m_pObservers{};
		int m_NumObservers{};

	};
}