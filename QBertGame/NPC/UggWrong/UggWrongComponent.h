#pragma once
#include "../NPCBaseComponent.h"

class UggWrongComponent : public NPCBaseComponent
{
public:
	explicit UggWrongComponent(const std::string& name, bool isUgg, int id, int spawnTile, int level = 1, float movementSpeed = 4.f);
	~UggWrongComponent() override = default;

	UggWrongComponent(const UggWrongComponent& other) = delete;
	UggWrongComponent(UggWrongComponent&& other) = delete;
	UggWrongComponent& operator=(const UggWrongComponent& other) = delete;
	UggWrongComponent& operator=(UggWrongComponent&& other) = delete;

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

private:
	bool m_bIsUgg;
};

