#pragma once
#include <document.h>
#include "../QBertStructs/QBertStructs.h"

class TileComponent;

namespace Idiot_Engine {
	class Scene;
	class GameObject;
}

class Level_1
{
public:
	Level_1() = default;
	void Load();
	void LoadTiles(Idiot_Engine::Scene& scene);

	std::vector<TileData> GetTiles() const;
private:
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> m_pTileObjects{};
	std::vector<TileData> m_pTiles{};
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_1{};
	glm::vec2 m_StartLocation{};

	std::vector<int> LoadLinkedTiles(const rapidjson::Value& val, const std::string& jsonKey)const;
};

