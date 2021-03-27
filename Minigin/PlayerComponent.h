#pragma once
#include "BaseComponent.h"

namespace Idiot_Engine
{
	class PlayerComponent : public BaseComponent
	{
	public:
		void FixedUpdate(const float deltaTime) override;
		void Update(const float deltaTime) override;
		void LateUpdate(const float deltaTime) override;
		void Render(const float nextFrame) const override;

		//void SetParent(Idiot_Engine::GameObject* parent) override;

		explicit PlayerComponent(const std::string& name);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Kill();
		void ChangeColor();
		void KillCoilyWithDisc();
		void RemainingDiscsScore();
		void CatchNPC();
	
	private:
		float m_Health{};
		int m_NrLives{};

		int m_Score{};
		int m_NrOfDiscsRemaining{};
	};
}
