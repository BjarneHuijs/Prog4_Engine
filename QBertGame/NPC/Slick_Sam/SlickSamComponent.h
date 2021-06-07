#pragma once
#include "../NPCBaseComponent.h"

class SlickSamComponent : public NPCBaseComponent
{
public:
	explicit SlickSamComponent(const std::string& name, bool isSlick, int id, int spawnTile, int level = 1, float movementSpeed = 4.f);
	~SlickSamComponent() override = default;

	SlickSamComponent(const SlickSamComponent& other) = delete;
	SlickSamComponent(SlickSamComponent&& other) = delete;
	SlickSamComponent& operator=(const SlickSamComponent& other) = delete;
	SlickSamComponent& operator=(SlickSamComponent&& other) = delete;

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
	bool m_bSlick;
};

