#pragma once
#include <ObserverComponent.h>
class NPCObserverComponent : public Idiot_Engine::ObserverComponent
{
public:
	explicit NPCObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types, const int level);

	void OnNotify(const Idiot_Engine::GameObject& object, const ObserverEvent& event) override;

private:
	int m_Level;
};

