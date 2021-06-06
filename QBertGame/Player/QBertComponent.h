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
	explicit QBertComponent(const std::string& name, int level = 1, float movementSpeed = 5.f);
	~QBertComponent() override = default;
	
	void FixedUpdate(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void LateUpdate(const float deltaTime) override;
	void Render(const float nextFrame) const override;
	
	void Kill() override;
	void ChangeColor(int tileIndex);
	void KillCoilyWithDisc();
	void RemainingDiscsScore();
	void CatchNPC();
	
	void MoveTopLeft();
	void MoveTopRight();
	void MoveBotLeft();
	void MoveBotRight();
	void SetPosOffset(float offset);

	int GetCurrentTileID() const;
	int GetCurrentLevelNr() const;
	void ResetToLevelStart();
	void DiscTaken();
	bool IsOnDisc() const;
	int GetDiscId() const;
	int GetNrOfLives() const;
	
	void SetCurrentLevel(const int level);

	void ResetLevels();
private:
	int m_NrLives{};
	int m_Score{};
	int m_NrOfDiscsRemaining{};

	int m_CurrentTile;
	int m_CurrentLevel;

	glm::vec2 m_TargetPos{};
	float m_CurrentMovementSpeed;
	float m_MovementSpeed;
	float m_LiftMovementSpeed;
	float m_PosOffset{};
	bool m_bMoving{};

	bool m_bOnDisc{};
	int m_DiscTarget{};
	int m_DiscId{};
	
	bool CheckForDisc(const int level);
	void ResetLevel(const int level);
};
