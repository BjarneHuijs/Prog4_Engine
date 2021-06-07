#pragma once
#include <Singleton.h>

struct DiscData;
struct TileData;
class TileManager : public Idiot_Engine::Singleton<TileManager>
{
public:
	void AddTile(TileData* tile);
	void AddDisc(DiscData* disc);
	std::vector<TileData*> GetTiles(const int level) const;
	std::vector<DiscData*> GetDiscs(const int level) const;
	TileData* GetTile(const int level, const int index) const;
	DiscData* GetDisc(const int level, const int index) const;

	bool LevelCleared(const int level);
	void ClearTiles(const int level);
private:
	friend class Singleton<TileManager>;
	TileManager() = default;
	~TileManager();
	std::vector<std::vector<TileData*>> m_pLevelTiles{};
	std::vector<std::vector<DiscData*>> m_pLevelDiscs{};
	//std::vector<TileData*> m_pTiles{};
};

