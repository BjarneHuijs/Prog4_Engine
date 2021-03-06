#pragma once
#include "Singleton.h"

namespace Idiot_Engine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void FixedUpdate(const float deltaTime);
		void Update(const float deltaTime);
		void LateUpdate(const float deltaTime);
		void Render(const float nextFrameTime);

		std::shared_ptr<Scene> GetScene(const int index) const;
		std::shared_ptr<Scene> GetScene(const std::string& name) const;

		void SetActiveScene(int sceneIndex);
		void SetActiveScene(const std::string& name);
		int GetActiveSceneIndex() const;
		std::shared_ptr<Scene> GetActiveScene() const;

		void CleanUp();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		~SceneManager();
		std::vector<std::shared_ptr<Scene>> m_Scenes{};

		int m_ActiveScene{};
		bool m_bSwapped{};
		float m_Swaptime{0.5f};
		float m_Swaptimer{0.f};
	};
}
