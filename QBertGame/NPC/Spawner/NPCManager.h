#pragma once
#include "SceneObject.h"
#include "Singleton.h"

namespace Idiot_Engine {
	class GameObject;
}

class NPCManager : public Idiot_Engine::Singleton<NPCManager>
{
public:
	NPCManager();
	
	void SpawnNpc();
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> GetNpcs() const;
	
	void SwitchLevel(int level);
	void RemoveNpc(int id);
	void ClearAllEnemies();
private:

	int m_CurrentLevel;
	bool m_bCoilyActive;
	int m_HighestId;
	std::vector<std::shared_ptr<Idiot_Engine::GameObject>> m_pNPCs;
	
};

