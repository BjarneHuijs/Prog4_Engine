#pragma once
#include <BaseComponent.h>
#include "../NPCBaseComponent.h"

class SlimeComponent : public NPCBaseComponent
{
public:
	explicit SlimeComponent(const std::string& name, bool isRedSlime, int id, int spawnTile, int level = 1, float movementSpeed = 4.f);
	~SlimeComponent() override = default;

	SlimeComponent(const SlimeComponent& other) = delete;
	SlimeComponent(SlimeComponent&& other) = delete;
	SlimeComponent& operator=(const SlimeComponent& other) = delete;
	SlimeComponent& operator=(SlimeComponent&& other) = delete;

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
	bool m_bRed;
};

