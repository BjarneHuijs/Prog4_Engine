#pragma once
#include "ObserverComponent.h"
#include "GameObject.h"

class PlayerObserverComponent : public Idiot_Engine::ObserverComponent
{
public:
	explicit PlayerObserverComponent(const std::string& name, const std::string& linkedComponentName, const std::vector<EventTypes>& types, const int level);

	void OnNotify(const Idiot_Engine::GameObject& object, const ObserverEvent& event) override;

private:
	int m_Level;
};

