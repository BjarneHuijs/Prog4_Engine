#pragma once
#include <BaseComponent.h>
enum class NPCTypes;

class SpawnerComponent : public Idiot_Engine::BaseComponent
{
	
public:
	SpawnerComponent(const std::string& name, int interval);

	//void SetSpawnInterval(float interval);

	void FixedUpdate(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void LateUpdate(const float deltaTime) override;
	void Render(const float nextFrame) const override;

	void SetNpcTypes(const std::vector<NPCTypes>& types);
private:
	const float m_SpawnInterval;
	float m_SpawnTimer;
	
	std::vector<NPCTypes> m_Types;
};

