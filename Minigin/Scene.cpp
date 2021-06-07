#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Idiot_Engine;

unsigned int Scene::m_IdCounter = 0;

std::string Scene::GetName() const
{
	return m_Name;
}

void Scene::RemoveObject(const std::shared_ptr<GameObject>& object)
{
	const auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [object](std::shared_ptr<GameObject> listObj)
		{
			return object == listObj;
		});

	if(it != m_Objects.end())
	{
		it->reset();
		m_Objects.erase(it);
	}
}

void Scene::CleanUp()
{
	std::_Erase_remove_if(m_Objects, [](std::shared_ptr<GameObject> object)
		{
			return object->IsMarkedForDelete();
		});
}

Scene::Scene(const std::string& name) : m_Name(name) {}


void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::FixedUpdate(const float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(deltaTime);
	}
}

void Scene::Update(const float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::LateUpdate(const float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate(deltaTime);
	}
}

void Scene::Render(const float nextFrameTime) const
{
	for (const auto& object : m_Objects)
	{
		object->Render(nextFrameTime);
	}
}

