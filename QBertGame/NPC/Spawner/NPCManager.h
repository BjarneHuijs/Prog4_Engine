#pragma once
#include "SceneObject.h"
#include "Singleton.h"

enum class NPCTypes;

namespace Idiot_Engine {
	class GameObject;
}

class NPCManager : public Idiot_Engine::Singleton<NPCManager>
{
public:
	NPCManager();

	void SpawnNpc(const std::vector<NPCTypes>& types);
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> GetNpcs() const;
	std::shared_ptr<Idiot_Engine::GameObject> GetNpc(int npcId) const;
	void SwitchLevel(int level);
	void RemoveNpc(int id);
	void ClearAllEnemies();
	void ClearAllButCoily();

	void FreezeNpcs();
	void UnPause();
private:

	int m_CurrentLevel;
	bool m_bCoilyActive;
	int m_HighestId;
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> m_pNPCs;
	bool m_bPaused;
	
	void SpawnSlime();
	void SpawnSlickSam();
	void SpawnCoily();
	void SpawnUggWrong();
};

