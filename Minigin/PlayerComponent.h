#pragma once
#include "BaseComponent.h"
namespace dae
{
	class PlayerComponent : public BaseComponent
	{
	public:
		void FixedUpdate(const float deltaTime) override;
		void Update(const float deltaTime) override;
		void LateUpdate(const float deltaTime) override;
		void Render(const float nextFrame) const override;

		//void SetParent(dae::GameObject* parent) override;

		explicit PlayerComponent();
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Kill();
	private:
		int m_Health{100};
	};
}