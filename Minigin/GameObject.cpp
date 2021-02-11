#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate(const float deltaTime) { deltaTime; }

void dae::GameObject::Update(const float deltaTime) { deltaTime; }

void dae::GameObject::LateUpdate(const float deltaTime) { deltaTime; }

void dae::GameObject::Render(const float nextFrameTime) const
{
	nextFrameTime;
	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component, const std::string componentName)
{
	m_pComponents.insert(std::make_pair(componentName, component));
}

void dae::GameObject::RemoveComponent(const std::string componentName)
{
	m_pComponents.erase(componentName);
}
