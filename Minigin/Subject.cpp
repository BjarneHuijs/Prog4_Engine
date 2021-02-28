#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

using namespace dae;
void Subject::AddObserver(Observer* pObserver)
{
	bool consequent{ true };
	for(auto* obj : m_pObservers)
	{
		if (obj == nullptr)
		{
			consequent = false;
		}
		
	}

	if (consequent) m_pObservers.push_back(pObserver);

}

void Subject::RemoveObserver(Observer* pObserver)
{
	for (size_t i{}; i < m_pObservers.size(); i++)
	{
		if (m_pObservers[i] == pObserver)
		{
			m_pObservers[i] = nullptr;
		}
		else if(m_pObservers[i] == nullptr)
		{
			if (m_pObservers[i] != m_pObservers.back()) 
			{
				m_pObservers[i] = m_pObservers[i + 1];
				m_pObservers[i + 1] = nullptr;
			}
		}

	}

	for(size_t i{ m_pObservers.size() - 1 }; i >= 0 ; i--)
	{
		if(m_pObservers[i] == nullptr)
		{
			m_pObservers.pop_back();
		}
	}
}

void dae::Subject::NotifyObservers(const GameObject& object, Event event)
{

	for (Observer* observer : m_pObservers)
	{
		observer->onNotify(object, event);
	}

}
