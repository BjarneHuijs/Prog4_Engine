#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate(const float deltaTime)
{	
	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Update(const float deltaTime) 
{
	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->Update(deltaTime);
	}
}

void dae::GameObject::LateUpdate(const float deltaTime)
{
	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->LateUpdate(deltaTime);
	}
}

void dae::GameObject::Render(const float nextFrameTime) const
{
	nextFrameTime;
	const auto pos = m_Transform.GetPosition();
	if(m_Texture)
	{		
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}

	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->Render(nextFrameTime);
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

const dae::Transform& dae::GameObject::GetPosition() const
{
	return m_Transform;
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component, const std::string componentName)
{
	//component->SetParent(weak_from_this());
	component->SetParent(this);
	m_pComponents.insert(std::make_pair(componentName, component));
}

void dae::GameObject::RemoveComponent(const std::string componentName)
{
	m_pComponents.erase(componentName);
}
