#pragma once
#include "BaseComponent.h"

namespace Idiot_Engine
{
	class PlayerComponent : public BaseComponent
	{
	public:
		virtual void FixedUpdate(const float deltaTime) override;
		virtual void Update(const float deltaTime) override;
		virtual void LateUpdate(const float deltaTime) override;
		virtual void Render(const float nextFrame) const override;

		//void SetParent(Idiot_Engine::GameObject* parent) override;

		explicit PlayerComponent(const std::string& name, int health = 1, int maxHealth = 1);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		virtual void Kill();
	
	protected:
		float m_Health{};
		float m_MaxHealth{};

	};
}
