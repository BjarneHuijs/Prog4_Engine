#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Idiot_Engine::SceneManager::FixedUpdate(const float deltaTime)
{
	const size_t size{ m_Scenes.size() };
	for (size_t i{}; i < size; i++)
	{
		if(i == m_ActiveScene)
			m_Scenes[i]->FixedUpdate(deltaTime);
	}
}

void Idiot_Engine::SceneManager::Update(const float deltaTime)
{
	const size_t size{ m_Scenes.size() };
	for (size_t i{}; i < size; i++)
	{
		if (i == m_ActiveScene)
			m_Scenes[i]->Update(deltaTime);
	}
}

void Idiot_Engine::SceneManager::LateUpdate(const float deltaTime)
{
	const size_t size{ m_Scenes.size() };
	for (size_t i{}; i < size; i++)
	{
		if (i == m_ActiveScene)
			m_Scenes[i]->LateUpdate(deltaTime);
	}
}

void Idiot_Engine::SceneManager::Render(const float nextFrameTime)
{
	const size_t size{ m_Scenes.size() };
	for (size_t i{}; i < size; i++)
	{
		if (i == m_ActiveScene)
			m_Scenes[i]->Render(nextFrameTime);
	}
}

std::shared_ptr<Idiot_Engine::Scene> Idiot_Engine::SceneManager::GetScene(const int index) const
{
	return m_Scenes[index];
}

std::shared_ptr<Idiot_Engine::Scene> Idiot_Engine::SceneManager::GetScene(const std::string& name) const
{
	for (int i{}; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->GetName()._Equal(name))
		{
			return m_Scenes[i];
		}
	}
	return nullptr;
}

void Idiot_Engine::SceneManager::SetActiveScene(int sceneIndex)
{
	m_ActiveScene = sceneIndex;
}

void Idiot_Engine::SceneManager::SetActiveScene(const std::string& name)
{
	for(int i{}; i < m_Scenes.size(); i++)
	{
		if(m_Scenes[i]->GetName()._Equal(name))
		{
			m_ActiveScene = i;
			return;
		}
	}
}

int Idiot_Engine::SceneManager::GetActiveSceneIndex() const
{
	return m_ActiveScene;
}

std::shared_ptr<Idiot_Engine::Scene> Idiot_Engine::SceneManager::GetActiveScene() const
{
	return m_Scenes.at(m_ActiveScene);
}

Idiot_Engine::SceneManager::~SceneManager()
{
	for(std::shared_ptr<Scene> scene : m_Scenes)
	{
		scene.reset();
		scene = nullptr;
	}
	
	m_Scenes.clear();
}

Idiot_Engine::Scene& Idiot_Engine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}


