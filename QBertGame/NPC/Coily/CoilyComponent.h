#pragma once
#include "../NPCBaseComponent.h"

class CoilyComponent : public NPCBaseComponent
{
public:
	CoilyComponent(const std::string& name, int id, int spawnTile, int level = 1, float movementSpeed = 4.f);
	~CoilyComponent() override = default;

	CoilyComponent(const CoilyComponent& other) = delete;
	CoilyComponent(CoilyComponent&& other) = delete;
	CoilyComponent& operator=(const CoilyComponent& other) = delete;
	CoilyComponent& operator=(CoilyComponent&& other) = delete;

	void FixedUpdate(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void LateUpdate(const float deltaTime) override;
	void Render(const float nextFrame) const override;

	void Kill() override;
	void Fall() override;

	void MoveTopLeft() override;
	void MoveTopRight() override;
	void MoveBotLeft() override;
	void MoveBotRight() override;

	void SetQBertTile(int tileId);
	
	bool IsEgg() const;
private:
	bool m_bEgg;
	int m_QBertTile;
};

