#pragma once
#include "Subject.h"
#include "Structs.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void onNotify(const GameObject& object, Event event) = 0;

	protected:
		EventTypes m_Type{};
	};
}