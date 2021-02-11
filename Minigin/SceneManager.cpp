#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::FixedUpdate(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Update(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::LateUpdate(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->LateUpdate(deltaTime);
	}
}

void dae::SceneManager::Render(const float nextFrameTime)
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render(nextFrameTime);
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const int index) const
{
	return m_Scenes[index];
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}


