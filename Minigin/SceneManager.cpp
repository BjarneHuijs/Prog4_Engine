#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Idiot_Engine::SceneManager::FixedUpdate(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void Idiot_Engine::SceneManager::Update(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void Idiot_Engine::SceneManager::LateUpdate(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->LateUpdate(deltaTime);
	}
}

void Idiot_Engine::SceneManager::Render(const float nextFrameTime)
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render(nextFrameTime);
	}
}

std::shared_ptr<Idiot_Engine::Scene> Idiot_Engine::SceneManager::GetScene(const int index) const
{
	return m_Scenes[index];
}

Idiot_Engine::Scene& Idiot_Engine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}


