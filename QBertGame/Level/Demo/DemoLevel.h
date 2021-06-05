#pragma once
#include "GameObject.h"

class DemoLevel
{
public:
	void Load();
	
private:
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_1{};
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_2{};

	void InitDemoInput(Idiot_Engine::GameObject* controllerObject, Idiot_Engine::GameObject* keyboardObject);
};

