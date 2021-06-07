#pragma once
#include <BaseComponent.h>
class NPCBaseComponent : public Idiot_Engine::BaseComponent
{
public:
	explicit NPCBaseComponent(const std::string& name, int id, int spawnTile, int level = 1, float movementSpeed = 4.f);
	explicit NPCBaseComponent(const BaseComponent& other) = delete;
	explicit NPCBaseComponent(BaseComponent&& other) = delete;

	virtual void FixedUpdate(const float deltaTime) override = 0;
	virtual void Update(const float deltaTime) override = 0;
	virtual void LateUpdate(const float deltaTime) override = 0;
	virtual void Render(const float nextFrame) const override = 0;

	virtual void Kill() = 0;
	virtual void Fall() = 0;

	virtual void MoveTopLeft() = 0;
	virtual void MoveTopRight() = 0;
	virtual void MoveBotLeft() = 0;
	virtual void MoveBotRight() = 0;
	void SetPosOffset(float offset);

	int GetCurrentTileID() const;
	int GetCurrentLevelNr() const;
	int GetNPC_ID() const;
	int IsDead() const;
protected:
	int m_NPC_ID;
	int m_CurrentTile;
	int m_CurrentLevel;

	glm::vec2 m_TargetPos{};
	float m_MovementSpeed;
	float m_PosOffset{};
	bool m_bMoving{};

	bool m_bFalling;
	bool m_bPaused;
	float m_PauseTime;
	float m_PauseTimer;

	bool m_bDead;
};

