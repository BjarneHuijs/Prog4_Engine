#include "QBertGamePCH.h"
#include "TileComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SpriteComponent.h"

TileComponent::TileComponent(int id, const std::vector<int>& moveTiles, const std::vector<int>& sideMoveTiles, float size)
	: BaseComponent("Tile_" + std::to_string(id))
	, m_Id(id)
	, m_Size(size)
	, m_CurrentState(TileStates::Base)
	, m_MoveTiles(moveTiles)
	, m_SideMoveTiles(sideMoveTiles)
{
	//m_pTileObject = std::make_shared<Idiot_Engine::GameObject>();

	////Hardcoded value 8 here since this is nr of tile sprites of entire game i will use -> no need to pass from elsewhere
	//m_pTexture = std::make_shared<Idiot_Engine::SpriteComponent>("Tile_" + id, 8);
	//
	//m_pTileObject->AddComponent(m_pTexture, m_pTexture->GetName());
	//m_pTexture->SetTexture("Tiles.png");
}

void TileComponent::FixedUpdate(const float)
{
}

void TileComponent::Update(const float)
{
}

void TileComponent::LateUpdate(const float)
{
}

void TileComponent::Render(const float) const
{

}

//void TileComponent::SetPosition(glm::vec2 position) const
//{
//	SetPosition(position.x, position.y);
//}

float TileComponent::GetSize() const
{
	return m_Size;
}

TileData TileComponent::GetTileData() const
{
	return TileData
	{
		m_Id,
		{},
		m_MoveTiles[0],
		m_MoveTiles[1],
		m_MoveTiles[2],
		m_MoveTiles[3],
		m_SideMoveTiles[0],
		m_SideMoveTiles[1]
	};
}
