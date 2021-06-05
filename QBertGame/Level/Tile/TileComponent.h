#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "../QBertStructs/QBertStructs.h"

namespace Idiot_Engine {
	class SpriteComponent;
	class Transform;
	class GameObject;
	class TextureComponent;
}

class TileComponent : public Idiot_Engine::BaseComponent
{
public:
	explicit TileComponent(int id, const std::vector<int>& moveTiles, const std::vector<int>& sideMoveTiles, float size = 50.f);
	virtual ~TileComponent() = default;

	void FixedUpdate(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void LateUpdate(const float deltaTime) override;
	void Render(const float nextFrame) const override;
	
	//void SetPosition(glm::vec2 position) const;
	//void SetPosition(const float x, const float y) const;
	//const Idiot_Engine::Transform& GetTransform() const;

	float GetSize() const;
	
	TileComponent(const TileComponent& other) = delete;
	TileComponent(TileComponent&& other) = delete;
	TileComponent& operator=(const TileComponent& other) = delete;
	TileComponent& operator=(TileComponent&& other) = delete;

	TileData GetTileData() const;

private:
	int m_Id;
	float m_Size;
	TileStates m_CurrentState;
	std::vector<int> m_MoveTiles;
	std::vector<int> m_SideMoveTiles;
	//std::shared_ptr<Idiot_Engine::GameObject> m_pTileObject{};
	//std::shared_ptr<Idiot_Engine::SpriteComponent> m_pTexture{};
};

