#include "QBertGamePCH.h"
#include "Tile.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureComponent.h"

Tile::Tile(int id, float size)
	: m_Id(id)
	, m_Size(size)
	, m_CurrentState(TileStates::Base)
{
	
	m_pTileObject = std::make_shared<Idiot_Engine::GameObject>();
	m_pTexture = std::make_shared<Idiot_Engine::TextureComponent>("Tile_" + id, 8);
	
	m_pTileObject->AddComponent(m_pTexture, m_pTexture->GetName());
	m_pTexture->SetTexture("Tiles.png");
}

std::shared_ptr<Idiot_Engine::GameObject> Tile::GetTileObject() const
{
	return m_pTileObject;
}

void Tile::SetPosition(glm::vec2 position) const
{
	SetPosition(position.x, position.y);
}

void Tile::SetPosition(const float x, const float y) const
{
	m_pTileObject->SetPosition(x, y);
}

const Idiot_Engine::Transform& Tile::GetTransform() const
{
	return m_pTileObject->GetTransform();
}

float Tile::GetSize() const
{
	return m_Size;
}
