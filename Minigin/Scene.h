#pragma once
#include "GameObject.h"
#include "SceneManager.h"

namespace Idiot_Engine
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render(float nextFrameTime) const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		
		std::string GetName() const;
		void RemoveObject(const std::shared_ptr<GameObject>& object);
		void CleanUp();
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
