#pragma once
#include "Structs.h"

namespace Idiot_Engine {
	class Transform;
	class GameObject;
	class TextureComponent;
}

enum class TileStates
{
	Base,
	Intermediate,
	Target,
};

class Tile
{
public:
	explicit Tile(int id, float size = 50.f);
	virtual ~Tile() = default;

	std::shared_ptr<Idiot_Engine::GameObject> GetTileObject() const;

	void SetPosition(glm::vec2 position) const;
	void SetPosition(const float x, const float y) const;
	const Idiot_Engine::Transform& GetTransform() const;

	float GetSize() const;
	
	Tile(const Tile& other) = delete;
	Tile(Tile&& other) = delete;
	Tile& operator=(const Tile& other) = delete;
	Tile& operator=(Tile&& other) = delete;

private:
	int m_Id;
	float m_Size;
	TileStates m_CurrentState;
	std::shared_ptr<Idiot_Engine::GameObject> m_pTileObject{};
	std::shared_ptr<Idiot_Engine::TextureComponent> m_pTexture{};
};

