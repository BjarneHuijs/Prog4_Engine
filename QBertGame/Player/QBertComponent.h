#pragma once
#include <PlayerComponent.h>

namespace Idiot_Engine {
	class Transform;
}

class GameLevels;
class TileComponent;
class QBertComponent : public Idiot_Engine::PlayerComponent
{
public:
	explicit QBertComponent(const std::string& name, int level = 1, float movementSpeed = 5.f);
	~QBertComponent() override = default;

	QBertComponent(const QBertComponent& other) = delete;
	QBertComponent(QBertComponent&& other) = delete;
	QBertComponent& operator=(const QBertComponent& other) = delete;
	QBertComponent& operator=(QBertComponent&& other) = delete;
	
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
	void StartNewGame(bool coop = false);

	bool IsCoop() const;
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

	bool m_bCoop;
	
	bool CheckForDisc(const int level);
	void ResetLevel(const int level);
};
