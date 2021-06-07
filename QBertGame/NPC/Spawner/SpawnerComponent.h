#pragma once
#include <BaseComponent.h>
class SpawnerComponent : public Idiot_Engine::BaseComponent
{
	
public:
	SpawnerComponent(const std::string& name, int interval);

	//void SetSpawnInterval(float interval);

	void FixedUpdate(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void LateUpdate(const float deltaTime) override;
	void Render(const float nextFrame) const override;

private:
	const float m_SpawnInterval;
	float m_SpawnTimer;
};

