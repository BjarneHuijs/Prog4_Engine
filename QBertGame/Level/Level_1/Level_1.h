#pragma once

class Tile;

namespace Idiot_Engine {
	class GameObject;
}

class Level_1
{
public:
	void Load();
	void LoadTiles();
private:
	std::vector<std::shared_ptr<Tile>> m_pTiles;
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_1{};
	glm::vec2 m_StartLocation;
};

