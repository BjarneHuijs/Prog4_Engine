#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "ObserverComponent.h"

using namespace Idiot_Engine;

SubjectComponent::SubjectComponent(const std::string& name)
	: BaseComponent(name)
{}

void SubjectComponent::AddObserver(ObserverComponent* pObserver)
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

void SubjectComponent::RemoveObserver(ObserverComponent* pObserver)
{
	const size_t size{ m_pObservers.size() };
	for (size_t i{}; i < size; i++)
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

	for(size_t i{ size - 1 }; i >= 0 ; i--)
	{
		if(m_pObservers[i] == nullptr)
		{
			m_pObservers.pop_back();
		}
	}
}

void SubjectComponent::NotifyObservers(const GameObject& object, const Event& event)
{

	for (ObserverComponent* observer : m_pObservers)
	{
		if(observer) observer->OnNotify(object, event);
	}

}
