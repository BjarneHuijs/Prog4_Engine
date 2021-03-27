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
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
