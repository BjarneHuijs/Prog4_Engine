#pragma once
#include "GameObject.h"

class Test
{
public:
	void Load();
	void Load2();
private:
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_1{};
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_2{};
};

