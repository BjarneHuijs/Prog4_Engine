#pragma once
#include <document.h>

#include "ServiceLocator.h"
#include "../../Structs_And_Menu/QBertStructs.h"

class TileComponent;
class QBertComponent;

namespace Idiot_Engine {
	class Scene;
	class GameObject;
}

class GameLevels
{
public:
	GameLevels();
	void LoadMainMenu();
	void LoadEndMenu();
	void LoadLevel(int levelNum);
	void LoadTiles(Idiot_Engine::Scene& scene, const std::ifstream& file);
	void InitAudio();
	void InitGameplayInput(const std::string& levelName);
	void InitMenuInput(const std::string& levelName);
	void InitQBert();

	std::shared_ptr<QBertComponent> GetQBert() const;
	std::shared_ptr<QBertComponent> GetQBert2() const;
private:
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> m_pTileObjects{};
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> m_pDiscObjects{};
	std::vector<TileData*> m_pTiles{};
	std::vector<DiscData*> m_pDiscs{};
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_1{};
	std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_2{};
	std::shared_ptr<Idiot_Engine::GameObject> m_pButtonObject{};
	//std::shared_ptr<Idiot_Engine::GameObject> m_pSpawner{};
	glm::vec2 m_StartLocation{};

	int m_SpawnerInterval{};
	int m_NrOfNPCTypes{};
	
	std::vector<int> LoadLinkedTiles(const rapidjson::Value& val, const std::string& jsonKey)const;
};

