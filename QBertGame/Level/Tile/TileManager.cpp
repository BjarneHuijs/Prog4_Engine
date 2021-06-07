#include "QBertGamePCH.h"
#include "TileManager.h"
#include "../../Structs_And_Menu/QBertStructs.h"

void TileManager::AddTile(TileData* tile)
{
	if(static_cast<int>(m_pLevelTiles.size()) < tile->LevelNr)
		m_pLevelTiles.push_back(std::vector<TileData*>());
	
	m_pLevelTiles[tile->LevelNr - 1].push_back(tile);
}

std::vector<TileData*> TileManager::GetTiles(const int level) const
{
	if (level < static_cast<int>(m_pLevelTiles.size()))
		return m_pLevelTiles.at(level);
	return {};
}

TileData* TileManager::GetTile(const int level, const int index) const
{
	if (level < static_cast<int>(m_pLevelTiles.size()) && index >= 0 )
	{
		return m_pLevelTiles.at(level).at(index);
	}
	return nullptr;
}

bool TileManager::LevelCleared(const int level)
{
	for (TileData* tile : m_pLevelTiles.at(level)) 
	{
		if (!tile->cleared) 
		{
			return false;
		}
	}
	ClearTiles(level);
	return true;
}

void TileManager::AddDisc(DiscData* disc)
{
	if (static_cast<int>(m_pLevelDiscs.size()) < disc->LevelNr)
		m_pLevelDiscs.push_back(std::vector<DiscData*>());

	m_pLevelDiscs[disc->LevelNr - 1].push_back(disc);
}

std::vector<DiscData*> TileManager::GetDiscs(const int level) const
{
	if (level < static_cast<int>(m_pLevelDiscs.size()))
		return m_pLevelDiscs.at(level);
	return {};
}

DiscData* TileManager::GetDisc(const int level, const int index) const
{
	if (level < static_cast<int>(m_pLevelDiscs.size()))

		return m_pLevelDiscs.at(level).at(index);
	return nullptr;
}

TileManager::~TileManager()
{
	for (std::vector<TileData*> levelTiles : m_pLevelTiles)
	{
		for (TileData* tile : levelTiles)
		{
			delete tile;
			tile = nullptr;
		}
	}

	for (std::vector <DiscData*> discs : m_pLevelDiscs)
	{
		for (DiscData* disc : discs)
		{
			delete disc;
			disc = nullptr;
		}
	}
}

void TileManager::ClearTiles(const int level)
{
	for (TileData* tile : m_pLevelTiles.at(level))
	{
		if (tile) 
		{
			tile->CurrentState = TileStates::Base;
			tile->cleared = false;
			tile->npcOnTile = false;
			tile->npcHostileOnTile = false;
		}
	}

	if (m_pLevelDiscs.size() > 0) 
	{
		for (DiscData* disc : m_pLevelDiscs.at(level))
		{
			if (disc)
			{
				disc->CurrentState = TileStates::Base;
				disc->Used = false;
			}
		}
	}
}


