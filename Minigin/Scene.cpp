#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Idiot_Engine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
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

