#pragma once
#include <document.h>

#include "ServiceLocator.h"
#include "../QBertStructs/QBertStructs.h"
#include "../Tile/Manager/TileManager.h"

class TileComponent;

namespace Idiot_Engine {
	class Scene;
	class GameObject;
}

class Level_1
{
public:
	Level_1();
	void LoadLevel(int levelNum);
	void LoadTiles(Idiot_Engine::Scene& scene, const std::ifstream& file);
	void InitAudio();
	void InitInput();
	void InitQBert();

private:
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> m_pTileObjects{};
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> m_pDiscObjects{};
	std::vector<TileData*> m_pTiles{};
	std::vector<DiscData*> m_pDiscs{};
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_1{};
	glm::vec2 m_StartLocation{};

	std::vector<int> LoadLinkedTiles(const rapidjson::Value& val, const std::string& jsonKey)const;
};

