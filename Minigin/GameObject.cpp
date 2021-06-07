#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

Idiot_Engine::GameObject::~GameObject()
{
	for(auto component : m_pComponents)
	{

		component.second.reset();
		//m_pComponents.erase();
	}
	m_pComponents.clear();
}

bool Idiot_Engine::GameObject::IsMarkedForDelete() const
{
	return m_bMarkedForDelete;
}

void Idiot_Engine::GameObject::MarkForDelete()
{
	m_bMarkedForDelete = true;
}

void Idiot_Engine::GameObject::FixedUpdate(const float deltaTime)
{	
	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->FixedUpdate(deltaTime);
	}
}

void Idiot_Engine::GameObject::Update(const float deltaTime) 
{
	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->Update(deltaTime);
	}
}

void Idiot_Engine::GameObject::LateUpdate(const float deltaTime)
{
	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->LateUpdate(deltaTime);
	}
}

void Idiot_Engine::GameObject::Render(const float nextFrameTime) const
{
	//nextFrameTime;

	for (const std::pair<std::string, std::shared_ptr<BaseComponent>> pComponent : m_pComponents)
	{
		pComponent.second->Render(nextFrameTime);
	}
}

//void Idiot_Engine::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void Idiot_Engine::GameObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

const Idiot_Engine::Transform& Idiot_Engine::GameObject::GetTransform() const
{
	return m_Transform;
}

void Idiot_Engine::GameObject::AddComponent(std::shared_ptr<BaseComponent> component, const std::string componentName)
{
	//component->SetParent(weak_from_this());
	component->SetParent(this);
	m_pComponents.insert(std::make_pair(componentName, component));
}

void Idiot_Engine::GameObject::RemoveComponent(const std::string componentName)
{
	m_pComponents.erase(componentName);
}
