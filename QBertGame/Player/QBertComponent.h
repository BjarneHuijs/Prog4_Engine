#pragma once
#include <PlayerComponent.h>

namespace Idiot_Engine {
	class Transform;
}

class Level_1;
class TileComponent;
class QBertComponent : public Idiot_Engine::PlayerComponent
{
public:
	explicit QBertComponent(const std::string& name, Level_1* pLevel = nullptr, float movementSpeed = 5.f);
	~QBertComponent() override = default;
	
	void FixedUpdate(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void LateUpdate(const float deltaTime) override;
	void Render(const float nextFrame) const override;
	
	void Kill() override;
	void ChangeColor();
	void KillCoilyWithDisc();
	void RemainingDiscsScore();
	void CatchNPC();

	void MoveTopLeft();
	void MoveTopRight();
	void MoveBotLeft();
	void MoveBotRight();
	void SetPosOffset(float offset);

private:
	int m_NrLives{};
	int m_Score{};
	int m_NrOfDiscsRemaining{};

	int m_CurrentTile;
	Level_1* m_pLevel;

	glm::vec2 m_TargetPos{};
	float m_MovementSpeed;
	float m_PosOffset{};
	bool m_bMoving{};
};

